/**
 * Blockly Demos: Code
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
 * @fileoverview JavaScript for Blockly's Code demo.
 * @author fraser@google.com (Neil Fraser)
 */
"use strict";
import { commandManager } from "./lib/commandManager.js";
import { eventManager } from "./lib/eventManager.js";
import { keyPressManager } from "./lib/keyPressManager.js";
/**
 * Create a namespace for the application.
 */
global.Code = {};

/**
 * Lookup for names of supported languages.  Keys should be in ISO 639 format.
 */
Code.LANGUAGE_NAME = {
  en: "English"
};

Code.eventListeners = [];
Code.workspaceCurrentCode = "";

global.callstopExternalEvent = function() {
  $.event.trigger({
    type: "stopExternalEvent",
    message: ""
  });
};

global.callChangeExternalEvent = function() {
  $.event.trigger({
    type: "eventChangeExternalEvent",
    message: ""
  });
};

var refreshTabCode = function(event) {
  var importStatement =
    DEVICE_TYPE === "codrone"
      ? CODRONE_IMPORT_STATEMENT
      : ZUMI_IMPORT_STATEMENT;
  if (
    event.type === Blockly.Events.DELETE ||
    event.type === Blockly.Events.CREATE
  ) {
  }
  if (event.type === Blockly.Events.CHANGE) {
    // Blockly.mainWorkspace.getAllBlocks().forEach(function(block){
    //   var svgRoot = block.getSvgRoot();
    //   console.log(block);
    //   svgRoot.setAttribute("id", block.type);
    // })
  }
  if (
    (event.type == Blockly.Events.CHANGE ||
      event.type == Blockly.Events.MOVE) &&
    Code.selected
  ) {
    var content = document.getElementById("content_" + Code.selected);
    var code = Blockly.JavaScript.workspaceToCode(Code.workspace);
    if (Code.workspaceCurrentCode !== code) {
      Code.workspaceCurrentCode = code;
      eventManager.removeAllEvents();
      keyPressManager.removeKeyPressEvents();
      global.callChangeExternalEvent();
    }
    if (content.id == "content_javascript") {
      content.textContent = code;
      if (typeof PR.prettyPrintOne == "function") {
        code = content.textContent;
        code = PR.prettyPrintOne(code, "js");
        content.innerHTML = code;
      }
    } else if (content.id == "content_python") {
      code = Blockly.Python.workspaceToCode(Code.workspace);
      content.textContent = code;
      if (typeof PR.prettyPrintOne == "function") {
        code = content.textContent;
        code = PR.prettyPrintOne(code, "py");
        content.innerHTML = importStatement + code;
      }
    } else if (content.id == "content_arduino") {
      code = Blockly.Python.workspaceToCode(Code.workspace);
      content.textContent = code;
      if (typeof PR.prettyPrintOne == "function") {
        code = content.textContent;
        code = PR.prettyPrintOne(code, "py");
        content.innerHTML = importStatement + code;
      }
    }
  }
};

let device = null;
function getSupportedProperties(characteristic) {
  let supportedProperties = [];
  for (const p in characteristic.properties) {
    if (characteristic.properties[p] === true) {
      supportedProperties.push(p.toUpperCase());
    }
  }
  return "[" + supportedProperties.join(", ") + "]";
}

Code.showNotification = function(Text) {
  var element = $("#notification");
  element.find("span").text(Text);
  element.addClass("show");
  setTimeout(function() {
    element.removeClass("show");
  }, 3000);
};

var readSingleFile = function(e) {
  Blockly.mainWorkspace.clear();
  var file = e.target.files[0];
  if (!file) {
    return;
  }
  var reader = new FileReader();
  reader.onload = function(e) {
    var contents = e.target.result;
    displayContents(contents);
  };
  reader.readAsText(file);
};

var displayContents = function(contents) {
  var xml = Blockly.Xml.textToDom(contents);
  Blockly.Xml.domToWorkspace(Blockly.mainWorkspace, xml);
};

Code.addClassToCategories = function() {
  var el = $(".blocklyTreeLabel");
  $.each(el, function(i, val) {
    var className = val.textContent.replace(" ", "-").toLowerCase();
    $(val).addClass(className);
  });
};
document
  .getElementById("file-input")
  .addEventListener("change", readSingleFile, false);

Code.createAndOpenFile = function(filename, xml) {
  var xmltext = Blockly.Xml.domToText(xml);
  var pom = document.createElement("a");

  var filename = filename + ".xml";
  var pom = document.createElement("a");
  var bb = new Blob([xmltext], { type: "text/plain" });

  pom.setAttribute("href", window.URL.createObjectURL(bb));
  pom.setAttribute("download", filename);

  pom.dataset.downloadurl = ["text/plain", pom.download, pom.href].join(":");
  pom.draggable = true;
  pom.classList.add("dragout");

  pom.click();
};

/**
 * List of RTL languages.
 */
Code.LANGUAGE_RTL = ["ar", "fa", "he", "lki"];

/**
 * Blockly's main workspace.
 * @type {Blockly.WorkspaceSvg}
 */
Code.workspace = null;

/**
 * Extracts a parameter from the URL.
 * If the parameter is absent default_value is returned.
 * @param {string} name The name of the parameter.
 * @param {string} defaultValue Value to return if paramater not found.
 * @return {string} The parameter value or the default value if not found.
 */
Code.getStringParamFromUrl = function(name, defaultValue) {
  var val = location.search.match(new RegExp("[?&]" + name + "=([^&]+)"));
  return val ? decodeURIComponent(val[1].replace(/\+/g, "%20")) : defaultValue;
};

/**
 * Get the language of this user from the URL.
 * @return {string} User's language.
 */
Code.getLang = function() {
  var lang = Code.getStringParamFromUrl("lang", "");
  if (Code.LANGUAGE_NAME[lang] === undefined) {
    // Default to English.
    lang = "en";
  }
  return lang;
};

/**
 * Is the current language (Code.LANG) an RTL language?
 * @return {boolean} True if RTL, false if LTR.
 */
Code.isRtl = function() {
  return Code.LANGUAGE_RTL.indexOf(Code.LANG) != -1;
};

/**
 * Load blocks saved on App Engine Storage or in session/local storage.
 * @param {string} defaultXml Text representation of default blocks.
 */
Code.loadBlocks = function(defaultXml) {
  try {
    var loadOnce = window.sessionStorage.loadOnceBlocks;
  } catch (e) {
    // Firefox sometimes throws a SecurityError when accessing sessionStorage.
    // Restarting Firefox fixes this, so it looks like a bug.
    var loadOnce = null;
  }
  if ("BlocklyStorage" in window && window.location.hash.length > 1) {
    // An href with #key trigers an AJAX call to retrieve saved blocks.
    BlocklyStorage.retrieveXml(window.location.hash.substring(1));
  } else if (loadOnce) {
    // Language switching stores the blocks during the reload.
    delete window.sessionStorage.loadOnceBlocks;
    var xml = Blockly.Xml.textToDom(loadOnce);
    Blockly.Xml.domToWorkspace(xml, Code.workspace);
  } else if (defaultXml) {
    // Load the editor with default starting blocks.
    var xml = Blockly.Xml.textToDom(defaultXml);
    Blockly.Xml.domToWorkspace(xml, Code.workspace);
  } else if ("BlocklyStorage" in window) {
    // Restore saved blocks in a separate thread so that subsequent
    // initialization is not affected from a failed load.
    window.setTimeout(BlocklyStorage.restoreBlocks, 0);
  }
};

/**
 * Save the blocks and reload with a different language.
 */
Code.changeLanguage = function() {
  // Store the blocks for the duration of the reload.
  // This should be skipped for the index page, which has no blocks and does
  // not load Blockly.
  // MSIE 11 does not support sessionStorage on file:// URLs.
  if (typeof Blockly != "undefined" && window.sessionStorage) {
    var xml = Blockly.Xml.workspaceToDom(Code.workspace);
    var text = Blockly.Xml.domToText(xml);
    window.sessionStorage.loadOnceBlocks = text;
  }

  var languageMenu = document.getElementById("languageMenu");
  var newLang = encodeURIComponent(
    languageMenu.options[languageMenu.selectedIndex].value
  );
  var search = window.location.search;
  if (search.length <= 1) {
    search = "?lang=" + newLang;
  } else if (search.match(/[?&]lang=[^&]*/)) {
    search = search.replace(/([?&]lang=)[^&]*/, "$1" + newLang);
  } else {
    search = search.replace(/\?/, "?lang=" + newLang + "&");
  }

  window.location =
    window.location.protocol +
    "//" +
    window.location.host +
    window.location.pathname +
    search;
};

/**
 * Bind a function to a button's click event.
 * On touch enabled browsers, ontouchend is treated as equivalent to onclick.
 * @param {!Element|string} el Button element or ID thereof.
 * @param {!Function} func Event handler to bind.
 */
Code.bindClick = function(el, func) {
  if (typeof el == "string") {
    el = document.getElementById(el);
  }
  el.addEventListener("click", func, true);
  el.addEventListener("touchend", func, true);
};

/**
 * Load the Prettify CSS and JavaScript.
 */
Code.importPrettify = function() {
  var script = document.createElement("script");
  script.setAttribute(
    "src",
    "https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js"
  );
  document.head.appendChild(script);
};

/**
 * Compute the absolute coordinates and dimensions of an HTML element.
 * @param {!Element} element Element to match.
 * @return {!Object} Contains height, width, x, and y properties.
 * @private
 */
Code.getBBox_ = function(element) {
  var height = element.offsetHeight;
  var width = element.offsetWidth;
  var x = 0;
  var y = 0;
  do {
    x += element.offsetLeft;
    y += element.offsetTop;
    element = element.offsetParent;
  } while (element);
  return {
    height: height,
    width: width,
    x: x,
    y: y
  };
};

/**
 * User's language (e.g. "en").
 * @type {string}
 */
Code.LANG = Code.getLang();

/**
 * List of tab names.
 * @private
 */
Code.TABS_ = ["blocks", "javascript", "python"];

Code.selected = "blocks";

/**
 * Switch the visible pane when a tab is clicked.
 * @param {string} clickedName Name of tab clicked.
 */
Code.tabClick = function(clickedName) {
  // Select the active tab.
  Code.selected = clickedName;
  // Show the selected pane.
  document.getElementById("content_" + clickedName).style.visibility =
    "visible";
  Code.renderContent();
  if (clickedName == "blocks") {
    Code.workspace.setVisible(true);
  }
  Blockly.svgResize(Code.workspace);
};

/**
 * Populate the currently selected pane with content generated from the blocks.
 */
Code.renderContent = function() {
  var content = document.getElementById("content_" + Code.selected);
  // Initialize the pane.
  if (content.id == "content_xml") {
    var xmlTextarea = document.getElementById("content_xml");
    var xmlDom = Blockly.Xml.workspaceToDom(Code.workspace);
    var xmlText = Blockly.Xml.domToPrettyText(xmlDom);
    xmlTextarea.value = xmlText;
    xmlTextarea.focus();
  } else if (content.id == "content_javascript") {
    var code = Blockly.JavaScript.workspaceToCode(Code.workspace);
    content.textContent = code;
    if (typeof PR.prettyPrintOne == "function") {
      code = content.textContent;
      code = PR.prettyPrintOne(code, "js");
      content.innerHTML = code;
    }
    if (Code.workspaceCurrentCode !== code) {
      Code.workspaceCurrentCode = code;
      eventManager.removeAllEvents();
      keyPressManager.removeKeyPressEvents();

      global.callstopExternalEvent();
    }
  } else if (content.id == "content_python") {
    code = Blockly.Python.workspaceToCode(Code.workspace);
    content.textContent = code;
    if (typeof PR.prettyPrintOne == "function") {
      code = content.textContent;
      code = PR.prettyPrintOne(code, "py");
      content.innerHTML =
        "drone = CoDrone.CoDrone()\n" + "drone.pair()\n\n" + code;
    }
  }
};

/**
 * Initialize Blockly.  Called on page load.
 */

Code.onresize = function(e) {
  var container = document.getElementById("content_area");
  var bBox = Code.getBBox_(container);
  for (var i = 0; i < Code.TABS_.length; i++) {
    var el = document.getElementById("content_" + Code.TABS_[i]);
    if (el) {
      el.style.top = bBox.y + "px";
      el.style.left = bBox.x + "px";
      // Height and width need to be set, read back, then set again to
      // compensate for scrollbars.
      el.style.height = bBox.height + "px";
      el.style.height = 2 * bBox.height - el.offsetHeight + "px";
      el.style.width = bBox.width + "px";
      el.style.width = 2 * bBox.width - el.offsetWidth + "px";
    }
  }
  // Make the 'Blocks' tab line up with the toolbox.
  if (Code.workspace && Code.workspace.toolbox_.width) {
    document.getElementById("tab_blocks").style.minWidth =
      Code.workspace.toolbox_.width - 38 + "px";
    // Account for the 19 pixel margin and on each side.
  }
};

Code.init = function() {
  Code.initLanguage();

  var rtl = Code.isRtl();
  var container = document.getElementById("content_area");
  // The toolbox XML specifies each category name using Blockly's messaging
  // format (eg. `<category name="%{BKY_CATLOGIC}">`).
  // These message keys need to be defined in `Blockly.Msg` in order to
  // be decoded by the library. Therefore, we'll use the `MSG` dictionary that's
  // been defined for each language to import each category name message
  // into `Blockly.Msg`.
  // TODO: Clean up the message files so this is done explicitly instead of
  // through this for-loop.
  for (var messageKey in MSG) {
    if (goog.string.startsWith(messageKey, "cat")) {
      Blockly.Msg[messageKey.toUpperCase()] = MSG[messageKey];
    }
  }

  // Construct the toolbox XML.
  var toolboxText = document.getElementById("juniorXml").outerHTML;
  var toolboxXml = Blockly.Xml.textToDom(toolboxText);

  Code.workspace = Blockly.inject("content_blocks", {
    grid: {
      spacing: 20,
      length: 40,
      colour: "#efefef",
      snap: true
    },
    media: "../../media/",
    rtl: rtl,
    toolbox: toolboxXml,
    zoom: {
      controls: true,
      wheel: true
    }
  });

  // Add to reserved word list: Local variables in execution environment (runJS)
  // and the infinite loop detection function.
  Blockly.JavaScript.addReservedWords("code,timeouts,checkTimeout");

  Code.loadBlocks("");

  Code.workspace.addChangeListener(refreshTabCode);

  if ("BlocklyStorage" in window) {
    // Hook a save function onto unload.
    BlocklyStorage.backupOnUnload(Code.workspace);
  }

  $("#juniorXmlBtn").click(function(e) {
    global.ZUMI_CURRENT_VIEW = "junior";
    $(".buttonTab").removeClass("active");
    $("#masterXml").hide();
    $(".master-workspace").hide();
    $(this).addClass("active");
    if (global.DEVICE_TYPE === "zumi") {
      var toolboxText = document.getElementById("juniorZumiXml").outerHTML;
    } else {
      var toolboxText = document.getElementById("juniorXml").outerHTML;
    }
    var toolboxXml = Blockly.Xml.textToDom(toolboxText);
    $(".blocklyToolboxDiv").attr("role", "junior");

    Code.workspace.updateToolbox(toolboxXml);
    Code.addClassToCategories();
  });

  $("#juniorZumiXmlBtn").click(function(e) {});

  $("#seniorXmlBtn").click(function(e) {
    global.ZUMI_CURRENT_VIEW = "senior";
    $(".buttonTab").removeClass("active");
    $("#masterXml").hide();
    $(".master-workspace").hide();
    $(this).addClass("active");
    if (global.DEVICE_TYPE === "zumi") {
      var toolboxText = document.getElementById("seniorZumiXml").outerHTML;
    } else {
      var toolboxText = document.getElementById("seniorXml").outerHTML;
    }
    var toolboxXml = Blockly.Xml.textToDom(toolboxText);
    $(".blocklyToolboxDiv").attr("role", "senior");
    Code.workspace.updateToolbox(toolboxXml);
    Code.addClassToCategories();
  });

  $("#masterXmlBtn").click(function(e) {
    global.ZUMI_CURRENT_VIEW = "master";
    Blockly.hideChaff();
    //document.getElementById("iframeJupyter").src = "";
    $(".buttonTab").removeClass("active");
    $(this).addClass("active");
    $("#masterXml").show();
    $(".master-workspace").show();
    var codeString = "";
    if (global.DEVICE_TYPE === "zumi") {
      codeString = ZUMI_IMPORT_STATEMENT;
    } else {
      codeString = CODRONE_IMPORT_STATEMENT;
    }
    var codeString =
      codeString + Blockly.Python.workspaceToCode(Code.workspace);
    var encodedString = window.btoa(unescape(encodeURIComponent(codeString)));
    var hostName = window.location.protocol + "//" + window.location.hostname;
    let zumiUrl = null;

    // if (global.ZUMI_URL) {
    //   document.getElementById("iframeJupyter").src =
    //     global.ZUMI_URL + "/notebooks/blockly.ipynb?src=" + encodedString;
    // } else {
    //   document.getElementById("iframeJupyter").src =
    //     hostName + ":8080/notebooks/blockly.ipynb?&src=" + encodedString;
    // }
    document.getElementById("iframeJupyter").style.visibility = "visible";
    var jupyterFrame = document.getElementById("iframeJupyter").contentWindow;
    jupyterFrame.postMessage(encodedString, "*");
  });

  Code.tabClick(Code.selected);

  Code.bindClick("trashButton", function() {
    Code.discard();
    Code.renderContent();
  });
  // Disable the link button if page isn't backed by App Engine storage.
  var linkButton = document.getElementById("linkButton");
  if ("BlocklyStorage" in window) {
    BlocklyStorage["HTTPREQUEST_ERROR"] = MSG["httpRequestError"];
    BlocklyStorage["LINK_ALERT"] = MSG["linkAlert"];
    BlocklyStorage["HASH_ERROR"] = MSG["hashError"];
    BlocklyStorage["XML_ERROR"] = MSG["xmlError"];
    Code.bindClick(linkButton, function() {
      BlocklyStorage.link(Code.workspace);
    });
  } else if (linkButton) {
    linkButton.className = "disabled";
  }

  for (var i = 0; i < Code.TABS_.length; i++) {
    var name = Code.TABS_[i];
    Code.bindClick(
      "tab_" + name,
      (function(name_) {
        return function() {
          Code.tabClick(name_);
        };
      })(name)
    );
  }
  Code.onresize();
  Blockly.svgResize(Code.workspace);

  // Lazy-load the syntax-highlighting.
  window.setTimeout(Code.importPrettify, 1);
  Blockly.Variables.createVariableNoPrompt(Code.workspace, null, "", "pitch");
  Blockly.Variables.createVariableNoPrompt(Code.workspace, null, "", "roll");
  Blockly.Variables.createVariableNoPrompt(Code.workspace, null, "", "yaw");
  Blockly.Variables.createVariableNoPrompt(
    Code.workspace,
    null,
    "",
    "throttle"
  );

  Code.loadWorkspace();
  $(".blocklyToolboxDiv").attr("role", "junior");
  $(".blocklyMainBackground").on("click", function() {
    var menuEl = $("#burgerMenu .menu");
    if (menuEl.hasClass("active")) {
      menuEl.removeClass("active");
    }
  });
  Code.addClassToCategories();
  // var p = $('svg')[0];
  // p.children[0].innerHTML = p.children[0].innerHTML + '<pattern id=\"img1\" patternUnits=\"userSpaceOnUse\" x=\"0\" y=\"-50\" width=\"150\" height=\"250\">\r\n<image xlink:href=\"https:\/\/localhost:8000\/src\/app\/images\/heartrate.gif\" width=\"150\" height=\"115\"><\/image> <\/pattern>'
};

/**
 * Initialize the page language.
 */
Code.initLanguage = function() {
  // Set the HTML's language and direction.
  var rtl = Code.isRtl();
  document.dir = rtl ? "rtl" : "ltr";
  document.head.parentElement.setAttribute("lang", Code.LANG);

  // Sort languages alphabetically.
  var languages = [];
  for (var lang in Code.LANGUAGE_NAME) {
    languages.push([Code.LANGUAGE_NAME[lang], lang]);
  }
  var comp = function(a, b) {
    // Sort based on first argument ('English', 'Русский', '简体字', etc).
    if (a[0] > b[0]) return 1;
    if (a[0] < b[0]) return -1;
    return 0;
  };
  // languages.sort(comp);
  // // Populate the language selection menu.
  // var languageMenu = document.getElementById('languageMenu');
  // languageMenu.options.length = 0;
  // for (var i = 0; i < languages.length; i++) {
  //   var tuple = languages[i];
  //   var lang = tuple[tuple.length - 1];
  //   var option = new Option(tuple[0], lang);
  //   if (lang == Code.LANG) {
  //     option.selected = true;
  //   }
  //   languageMenu.options.add(option);
  // }
  // languageMenu.addEventListener('change', Code.changeLanguage, true);

  // Inject language strings.
  document.title += " " + MSG["title"];
  //document.getElementById('title').textContent = MSG['title'];
  document.getElementById("tab_blocks").textContent = MSG["blocks"];

  document.getElementById("linkButton").title = MSG["linkTooltip"];
  document.getElementById("runButton").title = MSG["runTooltip"];
  document.getElementById("trashButton").title = MSG["trashTooltip"];
};

Code.loadWorkspace = function() {
  Blockly.mainWorkspace.clear();
  var projectName = "coDrone";

  if (typeof Storage !== "undefined") {
    if (localStorage.data !== null) {
      var xml = Blockly.Xml.textToDom(localStorage.getItem(projectName));
      Blockly.Xml.domToWorkspace(Blockly.mainWorkspace, xml);
    }
  } else {
    console.log("Storage is not support.");
  }
};

/**
 * Execute the user's code.
 * Just a quick and dirty eval.  Catch infinite loops.
 */
Code.runJS = function() {
  keyPressManager.addKeyPressCode(null, function() {});

  Blockly.JavaScript.INFINITE_LOOP_TRAP = "  checkTimeout();\n";
  var timeouts = 0;
  var checkTimeout = function() {
    if (timeouts++ > 100000000000) {
      throw MSG["timeout"];
    }
  };
  var code = Blockly.JavaScript.workspaceToCode(Code.workspace);
  Blockly.JavaScript.INFINITE_LOOP_TRAP = null;
  try {
    // add function to stop execution after block code
    eval("(async function(){" + code + " callstopExternalEvent();})()");
    //eval(code);
  } catch (e) {
    alert(MSG["badCode"].replace("%1", e));
  }
};

/**
 * Discard all blocks from the workspace.
 */
Code.discard = function() {
  var count = Code.workspace.getAllBlocks().length;
  if (
    count < 2 ||
    window.confirm(Blockly.Msg.DELETE_ALL_BLOCKS.replace("%1", count))
  ) {
    Code.workspace.clear();
    if (window.location.hash) {
      window.location.hash = "";
    }
  }
};

// Load the Code demo's language strings.
document.write('<script src="msg/' + Code.LANG + '.js"></script>\n');
// Load Blockly's language strings.
document.write('<script src="../../msg/js/' + Code.LANG + '.js"></script>\n');

window.addEventListener("load", Code.init);
