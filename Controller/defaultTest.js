const util = require("node:util");
const fs = require("node:fs");
const writeFile = util.promisify(fs.writeFile);
const execFile = util.promisify(require("node:child_process").execFile);
const exec = util.promisify(require("node:child_process").exec);
const rmdir = util.promisify(fs.rmdir);
const unlink = util.promisify(fs.unlink);
//const readFile = util.promisify(fs.readFile);
const path = require("path");

function rand(i, a = 0) {
    return Math.floor(Math.random() * (i - a + 1)) + a;
}

async function sendDefaultFiles(req, res, next) {
    const files = req.files;
    const { std_id, debug } = req.body;
    const events = [
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 95, 96, 97, 98, 112, 113, 114,
    ];
    const nums_of_testcases = 100;
    let not_pass = [];
    try {
        if (
            !files ||
            files.length != 2 ||
            !files.every(
                (file) =>
                    file.originalname == "knight2.h" ||
                    file.originalname == "knight2.cpp"
            )
        ) {
            throw (new Error("Error").message = "Invalid files");
        }

        await exec(
            `g++ -o ./${std_id}/main ./${std_id}/main.cpp ./${std_id}/knight2.cpp -std=c++11`
        );

        for (let i = 0; i < nums_of_testcases; i++) {
            const nums_events = rand(
                [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                    Math.floor(Math.random() * 10)
                ) * 1000,
                1
            );
            const nums_knight = rand(
                [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                    Math.floor(Math.random() * 10)
                ) * 500,
                1
            );
            let event = nums_events + "\n";
            let knight = nums_knight + "\n";
            let game_events = [];
            let knights = [];
            for (let i = 0; i < nums_events; i++)
                game_events.push(events[rand(events.length - 1)]);
            for (let i = 0; i < nums_knight; i++)
                knights.push(
                    [
                        rand(
                            [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                                Math.floor(Math.random() * 10)
                            ) * 999,
                            1
                        ),
                        rand(10, 1),
                        rand(10),
                        rand(
                            [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                                Math.floor(Math.random() * 10)
                            ) * 999
                        ),
                        rand(10),
                    ].join(" ")
                );
            if (Math.random() > 0.25) game_events.push(99);
            else
                game_events.push(
                    events[Math.floor(Math.random() * events.length)]
                );
            event += game_events.join(" ") + "\n";
            knight += knights.join("\n");
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
            if (outErr) throw outErr;

            let accepted = outOut == resultOut;

            if (!accepted) {
                not_pass.push({
                    knight_input: knight,
                    event_input: event,
                    output: outOut,
                    result: resultOut,
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
        if (err.stderr) {
            return res.status(502).send(err.stderr);
        }
        next(err);
    }
}

module.exports = {
    sendDefaultFiles,
};
