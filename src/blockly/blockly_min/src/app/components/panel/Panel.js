import React, { Component } from "react";
import ReactDOM from "react-dom";
import ContentTutorials from './ContentTutorials.js';
import ContentJupyter from './ContentJupyter.js';

class ContentJavascript extends React.Component {
  render() {
    return (
      <div className="content-panel content-2">
        <h1 style={{textAlign: 'center'}}>JavaScript</h1>
        <pre id="content_javascript" className="content"></pre>
      </div>
    );
  }
}

class ContentPython extends React.Component {
  render() {
    return (
      <div className="content-panel content-3">
        <h1 style={{textAlign: 'center'}}>Python</h1>
        <pre id="content_python" className="content"></pre>
      </div>
    );
  }
}

class ContentSensor extends React.Component {
  render() {
    return (
      <div className="content-panel content-4">
          <h3 style={{textAlign: 'center'}}>Sensor data as a right panel</h3>
          <div id="testSensorBatteryLabel">Battery porcentaje: <span id="batteryPercentageValue"></span></div>
      </div>
    );
  }
}

class Panel extends React.Component {
  constructor(props) {
   super(props);
   this.state = {isToggleOn: true};

   // This binding is necessary to make `this` work in the callback
   this.handleClick = this.handleClick.bind(this);
  }

  componentDidMount(){
    $(document).on(
      "zumiUrlChange",
      function() {
        var codeString = ZUMI_IMPORT_STATEMENT;
        var codeString = codeString + Blockly.Python.workspaceToCode(Code.workspace);
        var encodedString = window.btoa(unescape(encodeURIComponent(codeString)));

        let zumiUrl = null;
        var hostName = window.location.protocol +'//'+ window.location.hostname;
        if(global.BACKGROUND_RUNNING){
          zumiUrl =  hostName+':8080/notebooks/blockly.ipynb?run=1&src='+encodedString
        }
        else {
          zumiUrl = hostName+':8080/notebooks/blockly.ipynb?src='+encodedString;
        }

        global.BACKGROUND_RUNNING = false;

        document.getElementById('iframeJupyter').src = zumiUrl
      }.bind(this)
    );
    window.addEventListener('resize', Code.onresize, false);
    Code.onresize();
  }


  handleCloseClick(el) {
    el.preventDefault();
    // document.getElementById    // document.getElementById('rightPanel-1').style.width = '50%';
    // document.getElementsByClassName('loader')[0].style.display = 'block';
    // document.getElementById('iframeJupyter').style.visibility = 'hidden';
    // document.getElementById('rightPanel-1').classList.remove('active');('rightPanel-1').style.width = '50%';
    // document.getElementsByClassName('loader')[0].style.display = 'block';
    // document.getElementById('iframeJupyter').style.visibility = 'hidden';
    document.getElementById('rightPanel-1').classList.remove('active');
  }

  handleClick(el) {
    el.preventDefault();
    var panelId = el.currentTarget.dataset.panelId;
    var tab = el.currentTarget.dataset.tab;

    var activeTabButton = document.getElementsByClassName('show-right-panel active')[0];

    if (activeTabButton) {
      activeTabButton.classList.remove('active');
    }

    el.currentTarget.classList.add('active');

    if(panelId === '1'){
      document.getElementById('iframeTutorials').src = 'https://basecamp.robolink.com/cwists/category';
    }

    var activeTab = document.getElementsByClassName('content-panel active')[0];
    var contentTab = document.getElementsByClassName('content-' + panelId)[0];

    if (activeTab) {
      activeTab.classList.remove('active');
    }

    contentTab.classList.add('active');

    if (tab) {
      Code.tabClick(tab);
    }

    document.getElementById('rightPanel-1').classList.add('active');
  }

  render() {
    return (
        <div id="rightPanel-1">
          <a href="#" tabIndex="-1" className="close-right-panel" onClick={this.handleCloseClick}><i className="glyphicon glyphicon-remove"></i></a>
          <button className="show-right-panel" data-panel-id="1" onClick={this.handleClick}><img className="cap" src="./images/icons/graduation-cap.svg" />Tuts</button>
          <button className="show-right-panel" data-panel-id="3" data-tab="python" onClick={this.handleClick}><img src="./images/icons/python_icon_cropped.png" />Python</button>
          <button className="show-right-panel" data-panel-id="2" data-tab="javascript" onClick={this.handleClick}><img src="./images/icons/javascript_icon.png" />Javascript</button>
          <button className="show-right-panel" data-panel-id="5" onClick={this.handleClick}><img className="arduino" src="./images/icons/arduino_icon.png" />Arduino</button>

          <ContentTutorials />
          <ContentJavascript />
          <ContentPython />
          <ContentSensor />
          <ContentJupyter />
        </div>
    );
  }
}

export default Panel;
