const { Router } = require("express");
const {
    compileExecFiles,
    renderCompilePage,
} = require("../Controller/compile");

const compileRouter = new Router();

compileRouter.get("/", renderCompilePage);
compileRouter.post("/", compileExecFiles);

module.exports = compileRouter;
