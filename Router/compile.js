const { Router } = require("express");
const { compileExecFiles } = require("../Controller/compile");

const compileRouter = new Router();

compileRouter.get("/", compileExecFiles);

module.exports = compileRouter;
