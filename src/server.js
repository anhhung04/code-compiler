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
const readline = require("readline");
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
        if (!fs.existsSync("./uploads/mssv" + req.body.std_id))
            fs.mkdirSync("./uploads/mssv" + req.body.std_id);
        fs.copyFileSync(
            "./uploads/main.cpp",
            "./uploads/mssv" + req.body.std_id + "/main.cpp"
        );
        fs.copyFileSync(
            "./uploads/main.h",
            "./uploads/mssv" + req.body.std_id + "/main.h"
        );
        cb(null, "uploads/mssv" + req.body.std_id);
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
                files[0].originalname != "knight2.cpp" ||
                files[1].originalname != "knight2.h"
            ) {
                const error = new Error("Error");
                throw error;
            }

            await exec(
                `g++ -g -o ./uploads/mssv${std_id}/main ./uploads/mssv${std_id}/main.cpp ./uploads/mssv${std_id}/knight2.cpp -I . -std=c++11`
            );
            await delay(500);
            for (let i = 0; i < nums_of_testcases; i++) {
                const nums_events = rand(100);
                const nums_knight = rand(200);
                let event = nums_events + "\n";
                let knight = nums_knight + "\n";
                let game_events = [];
                let knights = [];
                for (let i = 0; i < nums_events; i++)
                    game_events.push(events[rand(events.length - 1)]);
                for (let i = 0; i < nums_knight; i++)
                    knights.push(
                        [
                            rand(999, 1),
                            rand(10, 1),
                            rand(10),
                            rand(999),
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
                await writeFile(`./uploads/mssv${std_id}/events.txt`, event);
                await writeFile(`./uploads/mssv${std_id}/knights.txt`, knight);
                await execFile(`./my_code/main.exe`, [
                    `../uploads/mssv${std_id}/knights.txt`,
                    `../uploads/mssv${std_id}/events.txt`,
                    `${std_id}`,
                ]);
                await execFile(`./uploads/mssv${std_id}/main.exe`, [
                    `./knights.txt`,
                    `./events.txt`,
                    `${std_id}`,
                ]);
                let knightData = await readFile(
                    `./uploads/mssv${std_id}/knights.txt`,
                    {
                        encoding: "utf-8",
                    }
                );
                let eventData = await readFile(
                    `./uploads/mssv${std_id}/events.txt`,
                    {
                        encoding: "utf-8",
                    }
                );
                let accepted = true;
                if (!accepted) {
                    let outData = [];
                    let outStream = fs.createReadStream(
                        path.join(
                            __dirname,
                            "../uploads/mssv" + std_id + "/output.txt"
                        )
                    );
                    const rlOut = readline.createInterface({
                        input: outStream,
                        crlfDelay: Infinity,
                    });
                    for await (const line of rlOut) {
                        outData.push(line);
                    }
                    let resultData = [];
                    const rlResult = readline.createInterface({
                        input: fs.createReadStream(
                            path.join(
                                __dirname,
                                "../uploads/mssv" + std_id + "/result.txt"
                            )
                        ),
                        crlfDelay: Infinity,
                    });
                    for await (const line of rlResult) {
                        resultData.push(line);
                    }
                    accepted = outData.every(
                        (value, index) => value == resultData[index]
                    );

                    if (!accepted) {
                        not_pass.push({
                            knight_input: knightData,
                            event_input: eventData,
                            output: outData,
                            result: resultData,
                        });
                    }
                }
                await unlink(
                    path.join(`./uploads/mssv${std_id}`, "result.txt")
                );
                await unlink(
                    path.join(`./uploads/mssv${std_id}`, "output.txt")
                );
            }

            for (const file of fs.readdirSync(`./uploads/mssv${std_id}`)) {
                await unlink(path.join(`./uploads/mssv${std_id}`, file));
            }
            await rmdir(`./uploads/mssv${std_id}`, {
                force: true,
            });
            //console.log(not_pass);
            res.render("result", {
                not_pass_tests: not_pass.length,
                not_pass: not_pass,
            });
        } catch (err) {
            err.httpStatusCode = 400;
            console.log(err);
            return res.status(500).send("Some thing went wrong");
        }
    }
);

app.get("/", function (req, res) {
    res.render("index");
});

app.listen(process.env.PORT || 3000, () =>
    console.log("Server started on port 3000")
);
