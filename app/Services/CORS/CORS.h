#pragma once
#include "../../crow/include/crow_all.h"
struct CORS {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        if (req.method == crow::HTTPMethod::Options) {
            res.code = 204;
            add_cors_headers(res);
            res.end();
        }
    }

    void after_handle(crow::request& req, crow::response& res, context&) {
        add_cors_headers(res);
    }

    void add_cors_headers(crow::response& res) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }
};
