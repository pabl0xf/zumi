import React, { Component } from "react";
import ReactDOM from "react-dom";

class MasterToolbox extends React.Component {
  componentDidMount() {
    this.state = { typeDevice: "codrone" };
    this.toggleOption = this.toggleOption.bind(this);
  }

  toggleOption(el) {
    var ul = el.target.parentElement;
    var li = ul.getElementsByTagName("li");
    var span = li[0].parentElement.getElementsByTagName("span");

    if (span[0].classList[2] === "glyphicon-triangle-bottom") {
      span[0].classList.remove("glyphicon-triangle-bottom");
      span[0].classList.add("glyphicon-triangle-top");
    } else {
      span[0].classList.remove("glyphicon-triangle-top");
      span[0].classList.add("glyphicon-triangle-bottom");
    }
    for (var i = 0; i < li.length; i++) {
      if (span[0].classList[2] === "glyphicon-triangle-bottom") {
        li[i].style.display = "block";
      } else {
        li[i].style.display = "none";
      }
    }
  }

  render() {
    return (
      <div className="master-toolbox">
        <ul>
          <div onClick={this.toggleOption}>
            Connection
            <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
          <li style={{ display: "none" }}>disconnect()</li>
          <li style={{ display: "none" }}>pair()</li>
          <li style={{ display: "none" }}>calibrate()</li>
        </ul>
        <ul>
          <div>
            {" "}
            Flight Commands (Start/Stop){" "}
            <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
        </ul>
        <ul>
          <div>
            {" "}
            Flight Commands (Movements){" "}
            <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
        </ul>
        <ul>
          <div>
            {" "}
            Flight Variables{" "}
            <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
        </ul>
        <ul>
          <div>
            {" "}
            LED <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
        </ul>
        <ul>
          <div>
            {" "}
            Status checkers{" "}
            <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
        </ul>
        <ul>
          <div>
            {" "}
            Sensors{" "}
            <span className="pull-right glyphicon glyphicon-triangle-top" />
          </div>
        </ul>
      </div>
    );
  }
}

export default MasterToolbox;
