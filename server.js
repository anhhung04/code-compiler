const express = require("express");
const bodyParser = require("body-parser");
const multer = require("multer");
const fs = require("fs");
const path = require("path");

const defaultTestRouter = require("./Router/defaultTest");
const compileRouter = require("./Router/compile");
const defaultRouter = require("./Router/index");
const memoryLeakRouter = require("./Router/memoryLeak");

const app = express();
//CREATE EXPRESS APP
app.use(bodyParser.urlencoded({ extended: true }));
app.set("views", path.join(__dirname, "./views"));
app.set("view engine", "ejs");

//ROUTES WILL GO HERE

const storage = multer.diskStorage({
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

const compileStorage = multer.diskStorage({
    destination: function (req, file, cb) {
        cb(null, "./my_code");
    },
    filename: function (req, file, cb) {
        cb(null, file.originalname);
    },
});

const upload = multer({ storage });
const uploadCompile = multer({ storage: compileStorage });

app.post("*", (req, res, next) => {
    if (req.path == "/compile") {
        return uploadCompile.array("myFiles", 3)(req, res, next);
    } else {
        return upload.array("myFiles", 2)(req, res, next);
    }
});
app.post("*", (req, res, next) => {
    const files = req.files;
    try {
        if (
            req.path != "/compile" &&
            (!files ||
                files.length != 2 ||
                !files.every(
                    (file) =>
                        file.originalname == "knight2.h" ||
                        file.originalname == "knight2.cpp"
                ))
        ) {
            throw (new Error("Error").message = "Invalid files");
        }
    } catch (err) {
        next(err);
    }
    next();
});

app.use("/defaultTest", defaultTestRouter);
app.use("/compile", compileRouter);
app.use("/", defaultRouter);
app.use("/memoryLeak", memoryLeakRouter);

app.listen(process.env.PORT || 3000, () =>
    console.log(`Server started on port ${process.env.PORT || 3000}`)
);

module.exports = app;
