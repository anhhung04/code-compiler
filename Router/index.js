const { Router } = require("express");
const { renderIndexPage } = require("../Controller/index");

const defaultRouter = new Router();

defaultRouter.get("/", renderIndexPage);

module.exports = defaultRouter;
