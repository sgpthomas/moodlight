// Generated by BUCKLESCRIPT VERSION 4.0.0, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Slider = require("./Slider.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");
var ToggleButton = require("./ToggleButton.js");

var component = ReasonReact.statelessComponent("Cosine");

function make(amp, period, phase, offset, timeDir, visible, onUpdate, _) {
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
          /* render */(function () {
              return React.createElement("div", undefined, ReasonReact.element(undefined, undefined, Slider.make(-10, 10, 0.1, amp, "Amplitude", (function (v) {
                                    return Curry._6(onUpdate, v, period, phase, offset, timeDir, visible);
                                  }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(0, 1, 0.001, period, "Period", (function (v) {
                                    return Curry._6(onUpdate, amp, v, phase, offset, timeDir, visible);
                                  }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(-500, 500, 1, phase, "Phase", (function (v) {
                                    return Curry._6(onUpdate, amp, period, -v, offset, timeDir, visible);
                                  }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(-2, 2, 0.1, offset, "Offset", (function (v) {
                                    return Curry._6(onUpdate, amp, period, phase, v, timeDir, visible);
                                  }), /* array */[])), ReasonReact.element(undefined, undefined, Slider.make(-30, 30, 1, timeDir, "Direction", (function (v) {
                                    return Curry._6(onUpdate, amp, period, phase, offset, v | 0, visible);
                                  }), /* array */[])), ReasonReact.element(undefined, undefined, ToggleButton.make(/* tuple */[
                                  "Show",
                                  "Hide"
                                ], visible, (function (b) {
                                    return Curry._6(onUpdate, amp, period, phase, offset, timeDir, b);
                                  }), /* array */[])));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */