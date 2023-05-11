const express = require("express");
const bodyParser = require("body-parser");
const multer = require("multer");
const fs = require("fs");
const path = require("path");

const defaultTestRouter = require("./Router/defaultTest");
const compileRouter = require("./Router/compile");
const defaultRouter = require("./Router/index");

const app = express();
//CREATE EXPRESS APP
app.use(bodyParser.urlencoded({ extended: true }));
app.set("views", path.join(__dirname, "./views"));
app.set("view engine", "ejs");

//ROUTES WILL GO HERE
app.use("/defaultTest", defaultTestRouter);
app.use("/compile", compileRouter);
app.use("/", defaultRouter);

app.listen(process.env.PORT || 3000, () =>
    console.log("Server started on port 3000")
);

module.exports = app;
