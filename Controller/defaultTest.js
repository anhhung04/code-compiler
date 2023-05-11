const util = require("node:util");
const fs = require("node:fs");
const writeFile = util.promisify(fs.writeFile);
const execFile = util.promisify(require("node:child_process").execFile);
const exec = util.promisify(require("node:child_process").exec);
const rmdir = util.promisify(fs.rmdir);
const unlink = util.promisify(fs.unlink);
const testcase = require("../Utils/generateTestcase");
//const readFile = util.promisify(fs.readFile);
const path = require("path");

async function sendDefaultFiles(req, res, next) {
    const nums_of_testcases = 100;
    const { std_id, debug } = req.body;
    let not_pass = [];
    try {
        const { stderr: compileErr } = await exec(
            `g++ -o ./${std_id}/main ./${std_id}/main.cpp ./${std_id}/knight2.cpp -std=c++11`
        );
        if (compileErr && compileErr.toLowerCase().includes("error"))
            throw compileErr;
        for (let i = 0; i < nums_of_testcases; i++) {
            let { event, knight } = testcase();
            await writeFile(`./${std_id}/events.txt`, event);
            await writeFile(`./${std_id}/knights.txt`, knight);
            const { stderr: resultErr, stdout: resultOut } = await execFile(
                path.join(__dirname, `../main${debug ? "Debug" : ""}`),
                [`./${std_id}/knights.txt`, `./${std_id}/events.txt`]
            );
            const { stderr: outErr, stdout: outOut } = await execFile(
                path.join(__dirname, "../" + std_id + "/main"),
                [`./${std_id}/knights.txt`, `./${std_id}/events.txt`]
            );
            if (resultErr) throw resultErr;

            let accepted = true;
            let outArr = outOut.split("\n");
            let resultArr = resultOut.split("\n");
            for (let i = 0; i < outArr.length; i++) {
                outArr[i] = {
                    text: outArr[i].trim().replace("\r", "").replace("\n", ""),
                    diff: false,
                };
                resultArr[i] = {
                    text: resultArr[i]
                        .trim()
                        .replace("\r", "")
                        .replace("\n", ""),
                    diff: false,
                };
                if (outArr[i].text != resultArr[i].text) {
                    outArr[i].diff = true;
                    resultArr[i].diff = true;
                    accepted = false;
                }
            }

            if (compileErr) {
                outArr.push({
                    text: compileErr,
                    diff: false,
                });
            }

            if (outErr) {
                outArr.push({
                    text: outErr,
                    diff: false,
                });
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
            await unlink(path.join(`./${std_id}`, file));
        }
        await rmdir(`./${std_id}`, {
            force: true,
        });
        //console.log(not_pass);
        res.render("result", {
            not_pass_tests: not_pass.length,
            not_pass: not_pass,
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
    sendDefaultFiles,
};
