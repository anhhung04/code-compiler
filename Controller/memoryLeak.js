const util = require("node:util");
const fs = require("fs");
const exec = util.promisify(require("node:child_process").exec);
const writeFile = util.promisify(fs.writeFile);
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
        for (let i = 0; i < 3; i++) {
            let { event, knight } = testcase();
            await writeFile(`./${std_id}/events.txt`, event);
            await writeFile(`./${std_id}/knights.txt`, knight);
            const { stderr: outErr, stdout: outOut } = await exec(
                `valgrind --tool=memcheck --leak-check=full ${path.join(
                    __dirname,
                    `../${std_id}/main`
                )} ./${std_id}/knights.txt ./${std_id}/events.txt`
            );
            if (outErr) throw outErr;
            res.render("result", {
                not_pass_tests: 0,
                not_pass: [],
            });
        }
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
