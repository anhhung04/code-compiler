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
                options: {
                    timeout: 2000
                }
            }
        });
        worker.on("message", (data) => {
            if (data.code == 139 || data.code == 11 || data.signal == "SIGSEGV") data.stdoutput += "\nSegmentation fault";
            let output = data.stdout;
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
                    timeout: 1000
                }
            }
        });
        worker.on("message", (data) => {
            if (data.code == 139 || data.code == 11 || data.signal == "SIGSEGV") data.stdout += "\nSegmentation fault";
            let output = data.stdout + "\n" + data.stderr;
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
                    timeout: 1000
                },
            }
        });
        worker.on("message", (data) => {
            if (data.code == 139 || data.code == 11 || data.signal == "SIGSEGV") data.stdout += "\nSegmentation fault";
            if (data.signal == "SIGTERM") data.stdout += "\nTime limit exceeded";
            let output = data.stdout + "\n" + data.stderr;
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

            if (outArr.length != resultArr.length) {
                accepted = false;
                let m = Math.min(outArr.length, resultArr.length);
                for (let i = 0; i < m; i++) {
                    if (outArr[i].text != resultArr[i].text) {
                        outArr[i].diff = true;
                        resultArr[i].diff = true;
                    }
                }
                if (outArr.length > resultArr.length) {
                    for (let i = m; i < outArr.length; i++) {
                        outArr[i].diff = true;
                    }
                } else {
                    for (let i = m; i < resultArr.length; i++) {
                        resultArr[i].diff = true;
                    }
                }
            } else {
                for (let i = 0; i < resultArr.length; i++) {
                    if (resultArr[i].text != outArr[i].text) {
                        resultArr[i].diff = true;
                        outArr[i].diff = true;
                        accepted = false;
                    }
                }
            }

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
