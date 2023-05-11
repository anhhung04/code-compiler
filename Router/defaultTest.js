const multer = require("multer");
const fs = require("fs");
const { Router } = require("express");
const { sendDefaultFiles } = require("../Controller/defaultTest");

const defaultTestRouter = new Router();

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

const upload = multer({ storage });
defaultTestRouter.post("/", upload.array("myFiles", 2), sendDefaultFiles);

module.exports = defaultTestRouter;
