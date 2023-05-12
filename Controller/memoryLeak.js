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
    const std_id = req.body.std_id;
    try {
        const { stdout, stderr: compileErr } = await exec(
            `g++ -o ./${std_id}/main ./${std_id}/main.cpp ./${std_id}/knight2.cpp -std=c++11`
        );
        
        leaked_test_cases = [];
        for (let i = 0; i < 5; i++) {
            let { event, knight } = testcase({
                max_events,
                max_knights,
                max_phoenix,
                max_antidote,
            });
            await writeFile(`./${std_id}/events.txt`, event);
            await writeFile(`./${std_id}/knights.txt`, knight);
            const { stderr: outErr, stdout: outOut } = await exec(
                `valgrind --leak-check=full ${path.join(
                    __dirname,
                    `../${std_id}/main`
                )} ./${std_id}/knights.txt ./${std_id}/events.txt`
            );

            if (!outErr.includes("All heap blocks were freed")) {
                leaked_test_cases.push({
                    event_input: event,
                    knight_input: knight,
                    output: outOut,
                    error:
                        compileErr +
                        "\n" +
                        outErr.split("\n").slice(4).join("\n"),
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
