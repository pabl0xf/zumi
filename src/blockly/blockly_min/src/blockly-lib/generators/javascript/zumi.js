/**
 * @license
 * Visual Blocks Language
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
 * @fileoverview Generating JavaScript for text blocks.
 * @author fraser@google.com (Neil Fraser)
 */
"use strict";

goog.provide("Blockly.JavaScript.zumi");

goog.require("Blockly.JavaScript");

Blockly.JavaScript["zumi_turn_degree_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "Engine.turnDegree(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_turn_left_junior"] = function(block) {
  return "Engine.turnLeft();\n";
};

Blockly.JavaScript["zumi_turn_right_junior"] = function(block) {
  return "Engine.turnRight();\n";
};

Blockly.JavaScript["zumi_forward_junior"] = function(block) {
  return "Engine.forward();\n";
};

Blockly.JavaScript["zumi_forward_duration_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "Engine.forward(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_reverse_junior"] = function(block) {
  return "Engine.reverse();\n";
};

Blockly.JavaScript["zumi_reverse_duration_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "Engine.reverse("+arg0+");\n";
};

Blockly.JavaScript["zumi_stop_junior"] = function(block) {
  return "Engine.stop();\n";
};

Blockly.JavaScript["zumi_get_distance_junior"] = function(block) {
  var arg0 = block.getFieldValue("TYPE");
  return ["Infrared.getDistance("+arg0+")", Blockly.JavaScript.ORDER_FUNCTION_CALL];
};

Blockly.JavaScript["zumi_play_sound_junior"] = function(block) {
  var arg0 = block.getFieldValue("SOUND");
  return "await play_sound(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_personality_act_junior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "await act(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_smile_detected_junior"] = function(block) {
  return "await smileDetected();\n";
};

Blockly.JavaScript["zumi_face_detected_junior"] = function(block) {
  return "await faceDetected();\n";
};

Blockly.JavaScript["zumi_track_face_junior"] = function(block) {
  return "await trackFace();\n";
};

Blockly.JavaScript["zumi_collect_smile_junior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "await collectSmile();\n";
};

Blockly.JavaScript["zumi_turn_degree_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "Engine.turnDegree(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_turn_left_senior"] = function(block) {
  return "Engine.turnLeft();\n";
};

Blockly.JavaScript["zumi_turn_right_senior"] = function(block) {
  return "Engine.turnRight();\n";
};

Blockly.JavaScript["zumi_forward_senior"] = function(block) {
  return "Engine.forward();\n";
};

Blockly.JavaScript["zumi_forward_duration_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "Engine.forward(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_reverse_senior"] = function(block) {
  return "Engine.reverse();\n";
};

Blockly.JavaScript["zumi_reverse_duration_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "Engine.reverse("+arg0+");\n";
};

Blockly.JavaScript["zumi_stop_senior"] = function(block) {
  return "Engine.stop();\n";
};

Blockly.JavaScript["zumi_get_distance_senior"] = function(block) {
  var arg0 = block.getFieldValue("TYPE");
  return ["Infrared.getDistance("+arg0+")", Blockly.JavaScript.ORDER_FUNCTION_CALL];
};

Blockly.JavaScript["zumi_play_sound_senior"] = function(block) {
  var arg0 = block.getFieldValue("SOUND");
  return "await play_sound(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_personality_act_senior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "await act(" + arg0 + ");\n";
};

Blockly.JavaScript["zumi_smile_detected_senior"] = function(block) {
  return "await smileDetected();\n";
};

Blockly.JavaScript["zumi_face_detected_senior"] = function(block) {
  return "await faceDetected();\n";
};

Blockly.JavaScript["zumi_track_face_senior"] = function(block) {
  return "await trackFace();\n";
};

Blockly.JavaScript["zumi_collect_smile_senior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "await collectSmile();\n";
};
