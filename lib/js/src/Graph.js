// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Pixel = require("./Pixel.js");
var Point = require("./Point.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("Graph");

var idRef = /* record */[/* contents */-1];

function nextPixel(size) {
  idRef[0] = idRef[0] + 1 | 0;
  return /* record */[
          /* id */idRef[0],
          /* size */size
        ];
}

function makePoints(num, size) {
  if (num !== 0) {
    if (num < 0) {
      return Pervasives.failwith("Need a positive size");
    } else {
      return /* :: */[
              nextPixel(size),
              makePoints(num - 1 | 0, size)
            ];
    }
  } else {
    return /* [] */0;
  }
}

function test(i, t) {
  return (i + t | 0) % 255 / 255;
}

function sumList(i, t, fList) {
  return List.fold_left((function (acc, f) {
                var match = Curry._2(f, i, t);
                return /* tuple */[
                        match[0] + acc[0],
                        match[1] + acc[1],
                        match[2] + acc[2]
                      ];
              }), /* tuple */[
              0,
              0,
              0
            ], fList);
}

function make(num, size, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */(function () {
              idRef[0] = -1;
              return /* record */[/* points */makePoints(num, size)];
            }),
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", {
                          id: "graph",
                          style: {
                            height: Pixel.string_of_px(size[/* y */1])
                          }
                        }, $$Array.of_list(List.map((function (point) {
                                    return ReasonReact.element(String(point[/* id */0]), undefined, Point.make(point[/* size */1], Math.sin(0.05 * point[/* id */0]), /* array */[]));
                                  }), self[/* state */1][/* points */0])));
            }),
          /* initialState */(function () {
              return /* record */[/* points */makePoints(num, size)];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (_, _$1) {
              return /* NoUpdate */0;
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.idRef = idRef;
exports.nextPixel = nextPixel;
exports.makePoints = makePoints;
exports.test = test;
exports.sumList = sumList;
exports.make = make;
/* component Not a pure module */