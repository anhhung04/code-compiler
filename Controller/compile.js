const fs = require("fs");
const util = require("util");
const unlink = util.promisify(fs.unlink);
const exec = util.promisify(require("child_process").exec);

async function compileExecFiles(req, res, next) {
    if (req.body.passwd != "adminupload294") {
        return res.status(500).send("Wrong password");
    }
    try {
        const { stderr: err1, stdout: out1 } = await exec(
            `g++ -o main ./my_code/main.cpp ./my_code/knight2.cpp -std=c++11`
        );
        const { stderr: err2, stdout: out2 } = await exec(
            `g++ -o mainDebug ./my_code/main.cpp ./my_code/knight2Debug.cpp  -std=c++11`
        );
        await unlink("./my_code/knight2.cpp");
        await unlink("./my_code/knight2Debug.cpp");
        await unlink("./my_code/knight2.h");
        if (err1 || err2) throw [err1, err2];
        res.send({
            stdout: [out1, out2],
            message: "Compile success",
        });
    } catch (err) {
        res.status(500).send(err);
    }
}

function renderCompilePage(req, res, next) {
    res.render("compile");
}

module.exports = {
    compileExecFiles,
    renderCompilePage,
};
