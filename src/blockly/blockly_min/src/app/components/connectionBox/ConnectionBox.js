import React, { Component } from "react";
import ReactDOM from "react-dom";

class ConnectionBox extends Component {
  constructor(props) {
    super(props);
    this.state = {
      isToggleOn: false,
      throttleSidewaysValue: 50,
      throttleValue: 50,
      roll: 50,
      pairButtonState: true
    };

    // This binding is necessary to make `this` work in the callback
    this.handlePair = this.handlePair.bind(this);
    this.handleReconnect = this.handleReconnect.bind(this);
    this.onDisconnected = this.onDisconnected.bind(this);
    this.closePannel = this.closePannel.bind(this);
    this.setThrottleSideways = this.setThrottleSideways.bind(this);
    this.setThrottle = this.setThrottle.bind(this);
    this.setRoll = this.setRoll.bind(this);
  }

  toggleDronesInfo(el) {
    el.preventDefault();

    var isHide = document
      .getElementById("connectMenu")
      .classList.contains("hide-info");

    if (isHide) {
      document.getElementById("connectMenu").classList.remove("hide-info");
      document
        .getElementsByClassName("blocklyToolboxDiv")[0]
        .classList.add("expand-connect");
    } else {
      document
        .getElementsByClassName("blocklyToolboxDiv")[0]
        .classList.remove("expand-connect");
      document.getElementById("connectMenu").classList.add("hide-info");
    }
  }

  setThrottleSideways(event) {
    this.setState({ throttleSidewaysValue: event.target.value });
  }

  setThrottle(event) {
    this.setState({ throttleValue: event.target.value });
  }

  setRoll(event) {
    this.setState({ roll: event.target.value });
  }

  connectDrone() {
    Code.selectedDrone.gatt
      .connect()
      .then(server => {
        Code.device = server;
        console.log("server", server);
        Code.deviceConnected = server.device.name;

        $("#scanButton").text("Disconnect");
        $("#coDroneLabel").show();
        $("#coDroneLabel").text(" Connected to " + Code.deviceConnected);
        $("#connectMenu").addClass("connected");
        $(".blocklyToolboxDiv").addClass("expand-connect");
        var deviceName = server.device.name.replace("PETRONE", "CoDrone");
        $(".petrone-id").text(deviceName);
        return server.getPrimaryService(PRIMARY_SERVICE);
      })
      .then(service => {
        Code.service = service;
        return service.getCharacteristic(WRITE_CHARACTERISTIC);
      })
      .then(characteristic => {
        Code.writeCharacteristic = characteristic;
        return Code.service.getCharacteristic(NOTIIFY_CHARACTERISTIC);
      })
      .then(characteristic => {
        Code.readCharacteristic = characteristic;
      })
      .catch(error => {
        console.log("Argh! " + error);
        //alert(error);
      });
  }

  handlePair(el) {
    if (global.DEVICE_TYPE === "zumi") {
      let zumiUrl = prompt("Please enter your Zümi remote address: ");
      if (zumiUrl != null) {
        global.ZUMI_URL = zumiUrl;
        $.event.trigger({
          type: "zumiUrlChange",
          message: ""
        });
      } else {
        alert("Error: Adress is required!");
      }
      return;
    } else {
      if (Code.device) {
        Code.device.disconnect();
        Code.device = null;
        $("#scanButton").text("Connect");
        $("#coDroneLabel").hide();
        $("#connectMenu").removeClass("connected");
      } else {
        console.log("Requesting any Bluetooth Device...");
        navigator.bluetooth
          .requestDevice({
            // filters: [...] <- Prefer filters to save energy & show relevant devices.
            acceptAllDevices: true,
            optionalServices: ["c320df00-7891-11e5-8bcf-feff819cdc9f"]
          })
          .then(device => {
            console.log("Connecting to GATT Server...");
            device.addEventListener(
              "gattserverdisconnected",
              this.onDisconnected
            );
            Code.selectedDrone = device;
            this.connectDrone();
            this.setState({
              pairButtonState: false
            });
          })
          .catch(error => {
            console.log("Argh! " + error);
            alert(error);
          });
      }
    }
  }

  handleReconnect() {
    if (Code.selectedDrone) {
      this.connectDrone();
    }
  }

  onDisconnected() {
    this.handlePair();
  }

  closePannel(el) {
    if (!this.state.isToggleOn) {
      this.setState({
        isToggleOn: true
      });
      $("#connectMenu").addClass("connected");
    } else {
      this.setState({
        isToggleOn: false
      });
      $("#connectMenu").removeClass("connected");
    }
  }

  render() {
    return (
      <div>
        <div className="toggle-drone-info">
          <a href="#" onClick={this.toggleDronesInfo} />
        </div>
        <p className="not-paired-text">
          <span className="circle" />
          Not Paired
        </p>
        <p className="paired-text">
          <span className="circle" />
          Paired: <span className="petrone-id">5617</span>
        </p>
        <div id="drones-info" className="drones-info">
          <span className="info1">Trimming</span>
          <div className="drone">
            <img src="./images/icons/drone-sideways.svg" />
            <div className="arrow">
              <input
                type="range"
                min="0"
                max="100"
                onChange={this.setThrottleSideways}
                value={this.state.throttleSidewaysValue}
                className="range1"
                orient="vertical"
              />
              <span>throttle: {this.state.throttleSidewaysValue}</span>
            </div>
          </div>
          <div className="drone drone2">
            <img
              className="img-arrow"
              src="./images/icons/drone-top-down.png"
            />
            <div className="arrow">
              <input
                type="range"
                min="0"
                max="100"
                onChange={this.setThrottle}
                value={this.state.throttleValue}
                className="range2"
                orient="vertical"
              />
              <span>throttle: {this.state.throttleValue}</span>
            </div>
            <div className="arrow2">
              <input
                type="range"
                min="0"
                max="100"
                onChange={this.setRoll}
                value={this.state.roll}
                className="range3"
              />
              <span>roll: {this.state.roll}</span>
            </div>
          </div>
        </div>
        <button
          type="button"
          onClick={this.handlePair}
          id="scanButton"
          className="btn btn-default navbar-btn"
        >
          Pair
        </button>
        <button
          type="button"
          onClick={this.handleReconnect}
          id="reconnectButton"
          className="btn btn-default navbar-btn"
          disabled={this.state.pairButtonState}
        >
          Pair with Previous
        </button>
        <div className="battery">
          <img className="" src="./images/icons/battery_full.svg" />
          <span>100%</span>
        </div>
      </div>
    );
  }
}

export default ConnectionBox;
