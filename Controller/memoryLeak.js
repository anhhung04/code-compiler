const util = require("util");
const fs = require("fs");
const writeFile = util.promisify(fs.writeFile);
const unlink = util.promisify(fs.unlink);
const rmdir = util.promisify(fs.rmdir);
const testcase = require("../Utils/generateTestcase");
const { Worker } = require("worker_threads");
const path = require("path");
function renderUploadFiles(req, res, next) {
    res.render("memoryLeak");
}

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
            let output = data.stdout + "\n" + data.stderr;
            if (data.code == 139 || data.code == 11) output += "\nSegmentation fault";
            res(output);
        });
        worker.on("error", (msg) => {
            rej(`An error ocurred: ${msg}`);
        });
    });
}

function runValgrindUserCode(user_id) {
    return new Promise((res, rej) => {
        const worker = new Worker("./Utils/runCommand.js", {
            workerData: {
                command: `valgrind`,
                args: [
                    `--leak-check=full`,
                    "--show-leak-kinds=all",
                    `${path.join(
                        __dirname,
                        `../${user_id}/main`)
                    }`,
                    `./${user_id}/knights.txt`,
                    `./${user_id}/events.txt`,
                ],
                options: {}
            }
        });
        worker.on("message", (data) => {
            let output = data.stdout;
            let errArr = data.stderr?.split("\n");
            for (let err of errArr) err = err?.trim().replace("\n", "").replace("\r", "")
            if (data.code == 139 || data.code == 11) output += "\nSegmentation fault";
            res({ output, error: errArr?.slice(errArr.findIndex(e => e.includes("HEAP SUMMARY"))).join("\n") });
        });
        worker.on("error", (msg) => {
            rej(`An error ocurred: ${msg}`);
        });
    });
}

async function sendMemoryLeakFiles(req, res, next) {
    const {
        max_testcases,
        max_events,
        max_knights,
        max_phoenix,
        max_antidote,
    } = req.body;
    const std_id = req.std_id;
    try {
        leaked_test_cases = [];
        const userCompileOutput = await compileUserCode(std_id);
        for (let i = 0; i < max_testcases; i++) {
            let { event, knight } = testcase({
                max_events,
                max_knights,
                max_phoenix,
                max_antidote,
            });
            await writeFile(`./${std_id}/events.txt`, event);
            await writeFile(`./${std_id}/knights.txt`, knight);
            const { output: userOutput, error } = await runValgrindUserCode(std_id);
            if (!error?.includes("All heap blocks were freed")) {
                leaked_test_cases.push({
                    event_input: event,
                    knight_input: knight,
                    output: userOutput,
                    error: error + "\n" + userCompileOutput,
                });
            }
        }
        for (const file of fs.readdirSync(`./${std_id}`)) {
            await unlink(path.join(`./${std_id}`, file));
        }
        await rmdir(`./${std_id}`, {
            force: true,
        });
        res.render("resultMemoryLeak", {
            leaked_test_cases: leaked_test_cases,
        });
    } catch (err) {
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
    renderUploadFiles,
    sendMemoryLeakFiles,
};
