/**
 * @license
 * Visual Blocks Editor
 *
 * Copyright 2012 Google Inc.
 * https://developers.google.com/blockly/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @fileoverview Text blocks for Blockly.
 * @author fraser@google.com (Neil Fraser)
 */
"use strict";

goog.provide("Blockly.Blocks.zumi"); // Deprecated
goog.provide("Blockly.Constants.Zumi");

goog.require("Blockly.Blocks");
goog.require("Blockly");

/**
 * Common HSV hue for all blocks in this category.
 * Should be the same as Blockly.Msg.TEXTS_HUE
 * @readonly
 */
Blockly.Constants.Zumi.HUE = "#3353da";
Blockly.Constants.Zumi.HUE_Orange2 = "#EC5B29";
Blockly.Constants.Zumi.HUE_Orange = "#f29327";
Blockly.Constants.Zumi.HUE_Violet = "#b358d7";
Blockly.Constants.Zumi.HUE_Rose = "#ee42ae";
Blockly.Constants.Zumi.HUE_Cian = "#3399e4";
Blockly.Constants.Zumi.HUE_flight_variables = "#33DAD8";
Blockly.Constants.Zumi.HUE_keyboard_input = "#CACACA";
Blockly.Constants.Zumi.HUE_timming = "#9B9B9B";
/** @deprecated Use Blockly.Constants.Text.HUE */
Blockly.Blocks.zumi.HUE = Blockly.Constants.Zumi.HUE;

Blockly.Blocks["zumi_turn_degree_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "turn %1 degrees",
      args0: [
        {
          type: "field_number",
          name: "NUM0",
          value: 0,
          min: -180,
          max: 180
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_turn_degree_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "turn_degree(%1º)",
      args0: [
        {
          type: "field_number",
          name: "NUM0",
          value: 0,
          min: -180,
          max: 180
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_turn_left_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "turn left",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_turn_left_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "turn_left()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_turn_right_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "turn right",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_turn_right_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "turn_right()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_forward_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "go forward forever",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_forward_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "forward()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_forward_duration_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "go forward for %1 seconds",
      args0: [
        {
          type: "field_number",
          name: "NUM0",
          value: 0,
          min: 0
        }
      ],
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_forward_duration_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "forward(%1 sec)",
      args0: [
        {
          type: "field_number",
          name: "NUM0",
          value: 0,
          min: 0
        }
      ],
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_reverse_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "reverse forever",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_reverse_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "reverse()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_reverse_duration_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "reverse for %1 seconds",
      args0: [
        {
          type: "field_number",
          name: "NUM0",
          value: 0,
          min: 0
        }
      ],
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_reverse_duration_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "reverse(%1 sec)",
      args0: [
        {
          type: "field_number",
          name: "NUM0",
          value: 0,
          min: 0
        }
      ],
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_go_direction_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "go(%1)",
      args0: [
        {
          type: "field_dropdown",
          name: "TYPE",
          options: [
            ["forward", "Direction.FORWARD"],
            ["backward", "Direction.BACKWARD"],
            ["left", "Direction.LEFT"],
            ["right", "Direction.RIGHT"]
          ]
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_stop_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "stop",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_stop_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "stop()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_camera_show_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "show",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};
Blockly.Blocks["zumi_camera_show_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "show()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_get_distance_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "get distance from %1 side",
      args0: [
        {
          type: "field_dropdown",
          name: "TYPE",
          options: [
            ["front", "Direction.FRONT"],
            ["back", "Direction.BACK"],
            ["left", "Direction.LEFT"],
            ["right", "Direction.RIGHT"]
          ]
        }
      ],
      output: "Number",
      colour: Blockly.Constants.Zumi.HUE_Orange,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_get_distance_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "get_distance(%1)",
      args0: [
        {
          type: "field_dropdown",
          name: "TYPE",
          options: [
            ["front", "Direction.FRONT"],
            ["back", "Direction.BACK"],
            ["left", "Direction.LEFT"],
            ["right", "Direction.RIGHT"]
          ]
        }
      ],
      output: "Number",
      colour: Blockly.Constants.Zumi.HUE_Orange,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_play_sound_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "play sound %1",
      args0: [
        {
          type: "field_dropdown",
          name: "SOUND",
          options: [
            ["happy", "Sound.HAPPY"],
            ["sad", "Sound.SAD"],
            ["honk", "Sound.HONK"]
          ]
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_play_sound_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "play_sound(%1)",
      args0: [
        {
          type: "field_dropdown",
          name: "SOUND",
          options: [
            ["happy", "Sound.HAPPY"],
            ["sad", "Sound.SAD"],
            ["honk", "Sound.HONK"]
          ]
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_personality_act_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "act %1",
      args0: [
        {
          type: "field_dropdown",
          name: "EMOTION",
          options: [
            ["happy", "Emotion.HAPPY"],
            ["sad", "Sound.SAD"],
            ["scared", "Sound.SCARED"],
            ["excited", "Sound.EXCITED"]
          ]
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_personality_act_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "act(%1)",
      args0: [
        {
          type: "field_dropdown",
          name: "EMOTION",
          options: [
            ["happy", "Emotion.HAPPY"],
            ["sad", "Sound.SAD"],
            ["scared", "Sound.SCARED"],
            ["excited", "Sound.EXCITED"]
          ]
        }
      ],
      previousStatement: null,
      nextStatement: null,
      colour: Blockly.Constants.Zumi.HUE,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_face_detected_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "face detected",
      output: "Boolean",
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_face_detected_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "face_detected()",
      output: "Boolean",
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_track_face_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "track face",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_track_face_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "track_face()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_take_photo_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "take photo",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_take_photo_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "take_photo()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_smile_detected_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "smile detected",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_smile_detected_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "smile_detected()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_collect_smile_junior"] = {
  init: function() {
    this.jsonInit({
      message0: "collect smile",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};

Blockly.Blocks["zumi_collect_smile_senior"] = {
  init: function() {
    this.jsonInit({
      message0: "collect_smile()",
      previousStatement: null,
      nextStatement: null,
      tooltip: Blockly.Msg.TEXT_JOIN_TOOLTIP,
      colour: Blockly.Blocks.codrone.HUE,
      helpUrl: Blockly.Msg.TEXT_JOIN_HELPURL
    });
  }
};
