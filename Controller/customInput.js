const { compileUserCode, runCode, runUserCode } = require("./defaultTest");
const fs = require("fs");
const util = require("util");
const path = require("path");
const writeFile = util.promisify(fs.writeFile);
const rmdir = util.promisify(fs.rmdir);
const unlink = util.promisify(fs.unlink);
async function customInputTest(req, res) {
    const {
        debug,
        event,
        knight
    } = req.body;
    const std_id = req.std_id;
    let not_pass = [];
    try {
        const compileErr = await compileUserCode(std_id);
        if (compileErr.error) throw compileErr.error;
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

        for (const file of fs.readdirSync(`./${std_id}`)) {
            await unlink(path.join(`./${std_id}`, file));
        }
        await rmdir(`./${std_id}`, {
            force: true,
        });
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
    customInputTest
};