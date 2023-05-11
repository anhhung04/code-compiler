const util = require("node:util");
const fs = require("fs");
const exec = util.promisify(require("node:child_process").exec);
const writeFile = util.promisify(fs.writeFile);
const unlink = util.promisify(fs.unlink);
const rmdir = util.promisify(fs.rmdir);
const testcase = require("../Utils/generateTestcase");
const path = require("path");
function renderUploadFiles(req, res, next) {
    res.render("memoryLeak");
}

async function sendMemoryLeakFiles(req, res, next) {
    try {
        const std_id = req.body.std_id;
        const { stdout, stderr: compileErr } = await exec(
            `g++ -o ./${std_id}/main ./${std_id}/main.cpp ./${std_id}/knight2.cpp -std=c++11`
        );
        if (compileErr) throw compileErr;
        leaked_test_cases = [];
        for (let i = 0; i < 5; i++) {
            let { event, knight } = testcase();
            await writeFile(`./${std_id}/events.txt`, event);
            await writeFile(`./${std_id}/knights.txt`, knight);
            const { stderr: outErr, stdout: outOut } = await exec(
                `valgrind --tool=memcheck --leak-check=full ${path.join(
                    __dirname,
                    `../${std_id}/main`
                )} ./${std_id}/knights.txt ./${std_id}/events.txt`
            );

            if (!outErr.includes("All heap were freed")) {
                leaked_test_cases.push({
                    output: outOut,
                    error: outErr.split("\n").slice(6).join("\n"),
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
            event: event_input,
            knight: knight_input,
            leaked_test_cases: leaked_test_cases,
        });
    } catch (err) {
        if (err.stderr) {
            return res.status(502).send(err.stderr);
        }
        next(err);
    }
}

module.exports = {
    renderUploadFiles,
    sendMemoryLeakFiles,
};
