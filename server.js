const express = require("express");
const bodyParser = require("body-parser");
const multer = require("multer");
const app = express();
const fs = require("fs");
const util = require("node:util");
const exec = util.promisify(require("node:child_process").exec);
const writeFile = util.promisify(fs.writeFile);
const execFile = util.promisify(require("node:child_process").execFile);
const rmdir = util.promisify(require("fs").rmdir);
const unlink = util.promisify(require("fs").unlink);
const readFile = util.promisify(require("fs").readFile);
const path = require("path");
//CREATE EXPRESS APP
app.use(bodyParser.urlencoded({ extended: true }));
app.set("views", path.join(__dirname, "./views"));
app.set("view engine", "ejs");

const delay = (ms) => new Promise((res) => setTimeout(res, ms));
function rand(i, a = 0) {
    return Math.floor(Math.random() * (i - a + 1)) + a;
}

var storage = multer.diskStorage({
    destination: function (req, file, cb) {
        if (!fs.existsSync("./" + req.body.std_id))
            fs.mkdirSync("./" + req.body.std_id);
        fs.copyFileSync("./main.cpp", "./" + req.body.std_id + "/main.cpp");
        fs.copyFileSync("./main.h", "./" + req.body.std_id + "/main.h");
        cb(null, "./" + req.body.std_id);
    },
    filename: function (req, file, cb) {
        cb(null, file.originalname);
    },
});

var upload = multer({ storage });
//ROUTES WILL GO HERE
app.post(
    "/uploadmultiple",
    upload.array("myFiles", 2),
    async (req, res, next) => {
        const files = req.files;
        const { std_id } = req.body;
        const events = [
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 95, 96, 97, 98, 112, 113, 114,
        ];
        const nums_of_testcases = 10;
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
                `g++ -g -o ./${std_id}/main ./${std_id}/main.cpp ./${std_id}/knight2.cpp -I . -std=c++11`
            );

            for (let i = 0; i < nums_of_testcases; i++) {
                const nums_events = rand(
                    [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                        Math.floor(Math.random() * 10)
                    ) * 1000
                );
                const nums_knight = rand(
                    [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1].at(
                        Math.floor(Math.random() * 10)
                    ) * 500
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
                                [
                                    0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
                                    1,
                                ].at(Math.floor(Math.random() * 10)) * 999,
                                1
                            ),
                            rand(10, 1),
                            rand(10),
                            rand(
                                [
                                    0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
                                    1,
                                ].at(Math.floor(Math.random() * 10)) * 999
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
                    path.join(__dirname, "./main.exe"),
                    [
                        `./${std_id}/knights.txt`,
                        `./${std_id}/events.txt`,
                        `${std_id}`,
                    ]
                );
                const { stderr: outErr, stdout: outOut } = await execFile(
                    path.join(__dirname, "./" + std_id + "/main.exe"),
                    [
                        `./${std_id}/knights.txt`,
                        `./${std_id}/events.txt`,
                        `${std_id}`,
                    ]
                );
                if (outErr) throw outErr;
                let knightData = await readFile(`./${std_id}/knights.txt`, {
                    encoding: "utf-8",
                });
                let eventData = await readFile(`./${std_id}/events.txt`, {
                    encoding: "utf-8",
                });
                let outData = await readFile(`./${std_id}/output.txt`, {
                    encoding: "utf-8",
                });
                let resultData = await readFile(`./${std_id}/result.txt`, {
                    encoding: "utf-8",
                });
                let accepted = outData == resultData;

                if (!accepted) {
                    not_pass.push({
                        knight_input: knightData,
                        event_input: eventData,
                        output: outData,
                        result: resultData,
                        diff: Diff.diffChars(outData, resultData),
                    });
                }
                await unlink(
                    path.join(__dirname, "./" + std_id + "/output.txt")
                );
                await unlink(
                    path.join(__dirname, "./" + std_id + "/result.txt")
                );
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
);

app.get("/", function (req, res) {
    res.render("index");
});

app.get("/reCompile", async function (req, res) {
    try {
        const { stderr, stdout } = await exec(
            `g++ -g -o main ./my_code/main.cpp ./my_code/knight2.cpp -I . -std=c++11`
        );
        if (stderr) throw stderr;
        res.send({
            stdout,
            message: "Compile success",
        });
    } catch (err) {
        res.json(500).send(err);
    }
});

app.listen(process.env.PORT || 3000, () =>
    console.log("Server started on port 3000")
);
