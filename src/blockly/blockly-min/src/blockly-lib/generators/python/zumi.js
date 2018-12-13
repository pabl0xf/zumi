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
 * @fileoverview Generating Python for logic blocks.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
"use strict";

goog.provide("Blockly.Python.zumi");

goog.require("Blockly.Python");

Blockly.Python["zumi_turn_degree_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.turn_degree(" + arg0 + ")\n";
};

Blockly.Python["zumi_turn_degree_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.turn_degree(" + arg0 + ")\n";
};

Blockly.Python["zumi_turn_left_junior"] = function(block) {
  return "engine.turn_left()\n";
};

Blockly.Python["zumi_turn_left_senior"] = function(block) {
  return "engine.turn_left()\n";
};

Blockly.Python["zumi_turn_right_junior"] = function(block) {
  return "engine.turn_right()\n";
};

Blockly.Python["zumi_turn_right_senior"] = function(block) {
  return "engine.turn_right()\n";
};

Blockly.Python["zumi_forward_junior"] = function(block) {
  return "engine.forward()\n";
};

Blockly.Python["zumi_forward_senior"] = function(block) {
  return "engine.forward()\n";
};

Blockly.Python["zumi_forward_duration_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.forward(" + arg0 + ")\n";
};

Blockly.Python["zumi_forward_duration_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.forward(" + arg0 + ")\n";
};

Blockly.Python["zumi_reverse_junior"] = function(block) {
  return "engine.reverse()\n";
};

Blockly.Python["zumi_reverse_senior"] = function(block) {
  return "engine.reverse()\n";
};

Blockly.Python["zumi_reverse_duration_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.reverse(" + arg0 + ")\n";
};

Blockly.Python["zumi_reverse_duration_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.reverse(" + arg0 + ")\n";
};

Blockly.Python["zumi_stop_junior"] = function(block) {
  return "engine.stop()\n";
};

Blockly.Python["zumi_stop_senior"] = function(block) {
  return "engine.stop()\n";
};

Blockly.Python["zumi_get_distance_junior"] = function(block) {
  var arg0 = block.getFieldValue("TYPE");
  return [
    "infrared.get_distance(" + arg0 + ")",
    Blockly.Python.ORDER_FUNCTION_CALL
  ];
};

Blockly.Python["zumi_play_sound_junior"] = function(block) {
  var arg0 = block.getFieldValue("SOUND");
  return "Audio.play_sound(" + arg0 + ")\n";
};

Blockly.Python["zumi_personality_act_junior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "personality.act(" + arg0 + ")\n";
};

Blockly.Python["zumi_face_detected_junior"] = function(block) {
  return ["camera.face_detected()", Blockly.Python.ORDER_ATOMIC];
};

Blockly.Python["zumi_track_face_junior"] = function(block) {
  return "camera.track_face()\n";
};

Blockly.Python["zumi_take_photo_junior"] = function(block) {
  return "camera.take_photo()\n";
};

Blockly.Python["zumi_smile_detected_junior"] = function(block) {
  return "DeepLearning.smile_detected()\n";
};

Blockly.Python["zumi_collect_smile_junior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "DeepLearning.collect_smile()\n";
};

Blockly.Python["zumi_get_distance_senior"] = function(block) {
  var arg0 = block.getFieldValue("TYPE");
  return [
    "infrared.get_distance(" + arg0 + ")",
    Blockly.Python.ORDER_FUNCTION_CALL
  ];
};

Blockly.Python["zumi_play_sound_senior"] = function(block) {
  var arg0 = block.getFieldValue("SOUND");
  return "Audio.play_sound(" + arg0 + ")\n";
};

Blockly.Python["zumi_personality_act_senior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "personality.act(" + arg0 + ")\n";
};

Blockly.Python["zumi_face_detected_senior"] = function(block) {
  return ["camera.face_detected()", Blockly.Python.ORDER_ATOMIC];
};

Blockly.Python["zumi_track_face_senior"] = function(block) {
  return "camera.track_face()\n";
};

Blockly.Python["zumi_take_photo_senior"] = function(block) {
  return "camera.take_photo()\n";
};

Blockly.Python["zumi_smile_detected_senior"] = function(block) {
  return "DeepLearning.smile_detected()\n";
};

Blockly.Python["zumi_collect_smile_senior"] = function(block) {
  var arg0 = block.getFieldValue("EMOTION");
  return "DeepLearning.collect_smile()\n";
};

Blockly.Python["zumi_camera_show_junior"] = function(block) {
  return "camera.show()\n";
};

Blockly.Python["zumi_camera_show_senior"] = function(block) {
  return "camera.show()\n";
};

Blockly.Python["zumi_get_distance_junior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.set_speed(" + arg0 + ")\n";
};

Blockly.Python["zumi_get_distance_senior"] = function(block) {
  var arg0 = block.getFieldValue("NUM0");
  return "engine.set_speed(" + arg0 + ")\n";
};
