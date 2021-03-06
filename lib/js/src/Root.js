// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var $$Set = require("bs-platform/lib/js/set.js");
var Line = require("./Line.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Panel = require("./Panel.js");
var React = require("react");
var Cosine = require("./Cosine.js");
var Slider = require("./Slider.js");
var Dropdown = require("./Dropdown.js");
var LedStrip = require("./LedStrip.js");
var RGBSlider = require("./RGBSlider.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");
var ToggleButton = require("./ToggleButton.js");

var PanelSet = $$Set.Make(/* Panel */[Panel.compare]);

var component = ReasonReact.reducerComponent("Root");

function floatify(f) {
  return Number(f.toString());
}

var pi = Math.PI;

function unwrapPanel(panel) {
  if (panel[/* visible */3]) {
    var match = panel[/* f */2];
    if (typeof match === "number") {
      return (function (_, _$1) {
          return /* tuple */[
                  0,
                  0,
                  0
                ];
        });
    } else {
      switch (match.tag | 0) {
        case 0 : 
            var timeDir = match[4];
            var offset = match[3];
            var phase = match[2];
            var period = match[1];
            var amp = match[0];
            return (function (i, t) {
                var v = amp * Math.cos(2 * pi * period * (i + t * -timeDir + Number(phase.toString()))) + Number(offset.toString());
                var match = panel[/* color */4];
                return /* tuple */[
                        match[0] * v,
                        match[1] * v,
                        match[2] * v
                      ];
              });
        case 1 : 
            var offset$1 = match[1];
            var slope = match[0];
            return (function (i, _) {
                var y = slope * (1 / 300) * i + Number(offset$1.toString());
                var match = panel[/* color */4];
                return /* tuple */[
                        match[0] * y,
                        match[1] * y,
                        match[2] * y
                      ];
              });
        case 2 : 
            return (function (_, _$1) {
                return /* tuple */[
                        0,
                        0,
                        0
                      ];
              });
        
      }
    }
  } else {
    return (function (_, _$1) {
        return /* tuple */[
                0,
                0,
                0
              ];
      });
  }
}

function attachNewTimer(state, send) {
  var match = state[/* timerId */4][0];
  if (match !== undefined) {
    return /* () */0;
  } else if (state[/* clockSpeed */2] > 0) {
    var timerId = setInterval((function () {
            return Curry._1(send, /* Tick */0);
          }), state[/* clockSpeed */2]);
    Curry._1(send, /* SetRunning */Block.__(0, [true]));
    state[/* timerId */4][0] = Js_primitive.some(timerId);
    return /* () */0;
  } else {
    state[/* timerId */4][0] = undefined;
    return /* () */0;
  }
}

function removeTimer(state, send) {
  var match = state[/* timerId */4][0];
  if (match !== undefined) {
    clearInterval(Js_primitive.valFromOption(match));
    Curry._1(send, /* SetRunning */Block.__(0, [false]));
    state[/* timerId */4][0] = undefined;
    return /* () */0;
  } else {
    return /* () */0;
  }
}

var default_001 = /* pixelSize : record */[
  /* x */3,
  /* y */97
];

var default_004 = /* timerId : record */[/* contents */undefined];

var default_005 = /* panels */PanelSet[/* empty */0];

var $$default = /* record */[
  /* pixelCount */387,
  default_001,
  /* clockSpeed */50,
  /* time */0,
  default_004,
  default_005,
  /* running */false
];

var panelId = /* record */[/* contents */-1];

function defaultPanel() {
  panelId[0] = panelId[0] + 1 | 0;
  return /* record */[
          /* id */panelId[0],
          /* name */"default",
          /* f : Nothing */0,
          /* visible */true,
          /* color : tuple */[
            0,
            0,
            0
          ]
        ];
}

var defaultCos = /* Cos */Block.__(0, [
    0.5,
    0.01,
    0,
    0.5,
    0
  ]);

var defaultLine = /* Line */Block.__(1, [
    1,
    0.0
  ]);

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", {
                          id: "root"
                        }, React.createElement("div", {
                              className: "row"
                            }, React.createElement("div", {
                                  className: "col"
                                }, React.createElement("h3", undefined, "Strip Controls"), ReasonReact.element(undefined, undefined, Slider.make(1, 50, 1, /* x */3, "X", (function (v) {
                                            return Curry._1(self[/* send */3], /* UpdateSize */Block.__(2, [
                                                          v | 0,
                                                          self[/* state */1][/* pixelSize */1][/* y */1]
                                                        ]));
                                          }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(1, 500, 1, /* y */97, "Y", (function (v) {
                                            return Curry._1(self[/* send */3], /* UpdateSize */Block.__(2, [
                                                          self[/* state */1][/* pixelSize */1][/* x */0],
                                                          v | 0
                                                        ]));
                                          }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(1, 500, 1, 387, "Count", (function (v) {
                                            return Curry._1(self[/* send */3], /* UpdateCount */Block.__(1, [v | 0]));
                                          }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(1, 200, 1, 50, "Speed", (function (v) {
                                            return Curry._1(self[/* send */3], /* UpdateClockSpeed */Block.__(3, [v | 0]));
                                          }), /* array */[])), React.createElement("h4", undefined, "Time: " + String(self[/* state */1][/* time */3])), React.createElement("div", undefined, React.createElement("button", {
                                          onMouseDown: (function () {
                                              return attachNewTimer(self[/* state */1], self[/* send */3]);
                                            }),
                                          onMouseUp: (function () {
                                              return removeTimer(self[/* state */1], self[/* send */3]);
                                            })
                                        }, "Tick!"), ReasonReact.element(undefined, undefined, ToggleButton.make(/* tuple */[
                                              "Start",
                                              "Stop"
                                            ], self[/* state */1][/* running */6], (function (b) {
                                                if (b) {
                                                  return attachNewTimer(self[/* state */1], self[/* send */3]);
                                                } else {
                                                  return removeTimer(self[/* state */1], self[/* send */3]);
                                                }
                                              }), /* array */[])), React.createElement("button", {
                                          onClick: (function () {
                                              return Curry._1(self[/* send */3], /* ResetTime */1);
                                            })
                                        }, "Reset")))), ReasonReact.element(undefined, undefined, LedStrip.make(self[/* state */1][/* pixelCount */0], self[/* state */1][/* pixelSize */1], self[/* state */1][/* time */3], List.map(unwrapPanel, Curry._1(PanelSet[/* elements */19], self[/* state */1][/* panels */5])), /* array */[])), React.createElement("div", {
                              className: "col"
                            }, React.createElement("button", {
                                  onClick: (function () {
                                      return Curry._1(self[/* send */3], /* NewPanel */2);
                                    })
                                }, "New Panel"), React.createElement("button", {
                                  onClick: (function () {
                                      return Curry._1(self[/* send */3], /* ResetPanels */3);
                                    })
                                }, "Delete All Panels")), React.createElement("div", {
                              className: "row"
                            }, $$Array.of_list(List.map((function (panel) {
                                        var match = panel[/* f */2];
                                        var tmp;
                                        if (typeof match === "number") {
                                          tmp = "Nothing";
                                        } else {
                                          switch (match.tag | 0) {
                                            case 0 : 
                                                tmp = ReasonReact.element(undefined, undefined, Cosine.make(match[0], match[1], match[2], match[3], match[4], (function (amp, period, phase, offset, timeDir) {
                                                            return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                            /* id */panel[/* id */0],
                                                                            /* name */panel[/* name */1],
                                                                            /* f : Cos */Block.__(0, [
                                                                                amp,
                                                                                period,
                                                                                phase,
                                                                                offset,
                                                                                timeDir
                                                                              ]),
                                                                            /* visible */panel[/* visible */3],
                                                                            /* color */panel[/* color */4]
                                                                          ]]));
                                                          }), /* array */[]));
                                                break;
                                            case 1 : 
                                                tmp = ReasonReact.element(undefined, undefined, Line.make(match[0], match[1], (function (slope, offset) {
                                                            return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                            /* id */panel[/* id */0],
                                                                            /* name */panel[/* name */1],
                                                                            /* f : Line */Block.__(1, [
                                                                                slope,
                                                                                offset
                                                                              ]),
                                                                            /* visible */panel[/* visible */3],
                                                                            /* color */panel[/* color */4]
                                                                          ]]));
                                                          }), /* array */[]));
                                                break;
                                            case 2 : 
                                                tmp = "[nyi] " + match[0];
                                                break;
                                            
                                          }
                                        }
                                        var match$1 = panel[/* color */4];
                                        return React.createElement("div", {
                                                    className: panel[/* visible */3] ? "col panel" : "col panel hidden"
                                                  }, React.createElement("span", undefined, String(panel[/* id */0])), React.createElement("span", undefined, ReasonReact.element(undefined, undefined, Dropdown.make(/* :: */[
                                                                "nothing",
                                                                /* :: */[
                                                                  "cos",
                                                                  /* :: */[
                                                                    "line",
                                                                    /* [] */0
                                                                  ]
                                                                ]
                                                              ], (function (param) {
                                                                  switch (param) {
                                                                    case "cos" : 
                                                                        return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                                        /* id */panel[/* id */0],
                                                                                        /* name */panel[/* name */1],
                                                                                        /* f */defaultCos,
                                                                                        /* visible */panel[/* visible */3],
                                                                                        /* color */panel[/* color */4]
                                                                                      ]]));
                                                                    case "line" : 
                                                                        return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                                        /* id */panel[/* id */0],
                                                                                        /* name */panel[/* name */1],
                                                                                        /* f */defaultLine,
                                                                                        /* visible */panel[/* visible */3],
                                                                                        /* color */panel[/* color */4]
                                                                                      ]]));
                                                                    case "nothing" : 
                                                                        return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                                        /* id */panel[/* id */0],
                                                                                        /* name */panel[/* name */1],
                                                                                        /* f : Nothing */0,
                                                                                        /* visible */panel[/* visible */3],
                                                                                        /* color */panel[/* color */4]
                                                                                      ]]));
                                                                    default:
                                                                      return /* () */0;
                                                                  }
                                                                }), /* array */[]))), React.createElement("span", undefined, tmp), React.createElement("span", undefined, ReasonReact.element(undefined, undefined, RGBSlider.make(match$1[0], match$1[1], match$1[2], (function (r, g, b) {
                                                                  return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                                  /* id */panel[/* id */0],
                                                                                  /* name */panel[/* name */1],
                                                                                  /* f */panel[/* f */2],
                                                                                  /* visible */panel[/* visible */3],
                                                                                  /* color : tuple */[
                                                                                    r,
                                                                                    g,
                                                                                    b
                                                                                  ]
                                                                                ]]));
                                                                }), /* array */[]))), React.createElement("span", {
                                                        className: "col"
                                                      }, React.createElement("div", undefined, ReasonReact.element(undefined, undefined, ToggleButton.make(/* tuple */[
                                                                    "Show",
                                                                    "Hide"
                                                                  ], panel[/* visible */3], (function (b) {
                                                                      return Curry._1(self[/* send */3], /* UpdatePanel */Block.__(4, [/* record */[
                                                                                      /* id */panel[/* id */0],
                                                                                      /* name */panel[/* name */1],
                                                                                      /* f */panel[/* f */2],
                                                                                      /* visible */b,
                                                                                      /* color */panel[/* color */4]
                                                                                    ]]));
                                                                    }), /* array */[]))), React.createElement("div", undefined, React.createElement("button", {
                                                                onClick: (function () {
                                                                    return Curry._1(self[/* send */3], /* DeletePanel */Block.__(5, [panel]));
                                                                  })
                                                              }, "Delete"))));
                                      }), Curry._1(PanelSet[/* elements */19], self[/* state */1][/* panels */5])))));
            }),
          /* initialState */(function () {
              return $$default;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                switch (action) {
                  case 0 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3] + 1 | 0,
                                  /* timerId */state[/* timerId */4],
                                  /* panels */state[/* panels */5],
                                  /* running */state[/* running */6]
                                ]]);
                  case 1 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */0,
                                  /* timerId */state[/* timerId */4],
                                  /* panels */state[/* panels */5],
                                  /* running */state[/* running */6]
                                ]]);
                  case 2 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */Curry._2(PanelSet[/* add */3], defaultPanel(/* () */0), state[/* panels */5]),
                                  /* running */state[/* running */6]
                                ]]);
                  case 3 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */PanelSet[/* empty */0],
                                  /* running */state[/* running */6]
                                ]]);
                  
                }
              } else {
                switch (action.tag | 0) {
                  case 0 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */state[/* panels */5],
                                  /* running */action[0]
                                ]]);
                  case 1 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */action[0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */state[/* panels */5],
                                  /* running */state[/* running */6]
                                ]]);
                  case 2 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize : record */[
                                    /* x */action[0],
                                    /* y */action[1]
                                  ],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */state[/* panels */5],
                                  /* running */state[/* running */6]
                                ]]);
                  case 3 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */action[0],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */state[/* panels */5],
                                  /* running */state[/* running */6]
                                ]]);
                  case 4 : 
                      var p = action[0];
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */Curry._2(PanelSet[/* add */3], p, Curry._2(PanelSet[/* remove */5], p, state[/* panels */5])),
                                  /* running */state[/* running */6]
                                ]]);
                  case 5 : 
                      return /* Update */Block.__(0, [/* record */[
                                  /* pixelCount */state[/* pixelCount */0],
                                  /* pixelSize */state[/* pixelSize */1],
                                  /* clockSpeed */state[/* clockSpeed */2],
                                  /* time */state[/* time */3],
                                  /* timerId */state[/* timerId */4],
                                  /* panels */Curry._2(PanelSet[/* remove */5], action[0], state[/* panels */5]),
                                  /* running */state[/* running */6]
                                ]]);
                  
                }
              }
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.PanelSet = PanelSet;
exports.component = component;
exports.floatify = floatify;
exports.pi = pi;
exports.unwrapPanel = unwrapPanel;
exports.attachNewTimer = attachNewTimer;
exports.removeTimer = removeTimer;
exports.$$default = $$default;
exports.default = $$default;
exports.__esModule = true;
exports.panelId = panelId;
exports.defaultPanel = defaultPanel;
exports.defaultCos = defaultCos;
exports.defaultLine = defaultLine;
exports.make = make;
/* PanelSet Not a pure module */
