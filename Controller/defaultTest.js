const util = require("util");
const fs = require("fs");
const path = require("path");
const { Worker } = require("worker_threads");
const writeFile = util.promisify(fs.writeFile);
const rmdir = util.promisify(fs.rmdir);
const unlink = util.promisify(fs.unlink);
const testcase = require("../Utils/generateTestcase");

function compileUserCode(user_id) {
    return new Promise((res, rej) => {
        const worker = new Worker("./Utils/runCommand.js", {
            workerData: {
                command: "g++",
                args: [
                    "-o",
                    `./${user_id}/main`,
                    `./${user_id}/main.cpp`,
                    `./${user_id}/knight2.cpp`,
                    "-std=c++11",
                ],
                options: {}
            }
        });
        worker.on("message", (data) => {
            let output = data.stdout;
            if (data.code == 139 || data.code == 11) output += "\nSegmentation fault";
            res({ output, error: data.stderr });
        });
        worker.on("error", (msg) => {
            rej(`An error ocurred: ${msg}`);
        });
    });
}

function runCode(debug, user_id) {
    return new Promise((res, rej) => {
        const worker = new Worker("./Utils/runCommand.js", {
            workerData: {
                command: `./main${debug ? "Debug" : ""}`,
                args: [
                    `./${user_id}/knights.txt`,
                    `./${user_id}/events.txt`,
                ],
                options: {
                    maxBuffer: 1024 * 1024 * 1024,
                }
            }
        });
        worker.on("message", (data) => {
            let output = data.stdout + "\n" + data.stderr;
            if (data.code == 139 || data.code == 11) output += "\nSegmentation fault";
            res(output);
        });
        worker.on("error", (msg) => {
            rej(`An error ocurred: ${msg}`);
        });
    });
}

function runUserCode(user_id) {
    return new Promise((res, rej) => {
        const worker = new Worker("./Utils/runCommand.js", {
            workerData: {
                command: `./${user_id}/main`,
                args: [
                    `./${user_id}/knights.txt`,
                    `./${user_id}/events.txt`,
                ],
                options: {
                    maxBuffer: 1024 * 1024 * 1024,
                },
            }
        });
        worker.on("message", (data) => {
            let output = data.stdout + "\n" + data.stderr;
            if (data.code == 139 || data.code == 11) output += "\nSegmentation fault";
            res(output);
        });
        worker.on("error", (msg) => {
            rej(`An error ocurred: ${msg}`);
        });
    });
}

async function sendDefaultFiles(req, res, next) {
    const {
        debug,
        max_testcases,
        max_events,
        max_knights,
        max_phoenix,
        max_antidote,
    } = req.body;
    const std_id = req.std_id;
    let not_pass = [];
    try {
        const compileErr = await compileUserCode(std_id);
        if (compileErr.error) throw compileErr.error;
        for (let i = 0; i < max_testcases; i++) {
            let { event, knight } = testcase({
                max_events,
                max_knights,
                max_phoenix,
                max_antidote,
            });
            await writeFile(`./${std_id}/events.txt`, event);
            await writeFile(`./${std_id}/knights.txt`, knight);
            const [resultOutput, userOutput] = await Promise.all([runCode(debug, std_id), runUserCode(std_id)]);
            let accepted = true;
            let outArr = userOutput.split("\n");
            let resultArr = resultOutput.split("\n");
            for (let i = 0; i < outArr.length; i++) {
                if (outArr[i]) outArr[i] = outArr[i].trim().replace("\r", "").replace("\n", "");
                outArr[i] = {
                    text: outArr[i],
                    diff: false,
                };
            }
            for (let i = 0; i < resultArr.length; i++) {
                if (resultArr[i]) resultArr[i] = resultArr[i].trim().replace("\r", "").replace("\n", "");
                resultArr[i] = {
                    text: resultArr[i],
                    diff: false,
                };
            }

            accepted = outArr.length == resultArr.length && resultArr.every((v, i) => v.text === outArr[i].text);

            if (!accepted) {
                not_pass.push({
                    knight_input: knight,
                    event_input: event,
                    output: outArr,
                    result: resultArr,
                });
            }
        }

        for (const file of fs.readdirSync(`./${std_id}`)) {
            await unlink(path.join(__dirname, `../${std_id}`, file));
        }
        await rmdir(`./${std_id}`, {
            force: true,
        });
        res.render("result", {
            not_pass_tests: not_pass.length,
            not_pass: not_pass,
        });
    } catch (err) {
        console.log(err);
        if (fs.existsSync("./" + std_id)) {
            for (const file of fs.readdirSync(`./${std_id}`)) {
                await unlink(path.join(`./${std_id}`, file));
            }
            await rmdir(`./${std_id}`, {
                force: true,
            });
        }
        return res.status(500).send(err);
    }
}

module.exports = {
    sendDefaultFiles,
    runCode,
    runUserCode,
    compileUserCode
};
