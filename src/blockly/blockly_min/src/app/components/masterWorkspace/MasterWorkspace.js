import React, { Component } from "react";
import ReactDOM from "react-dom";

class MasterWorkspace extends React.Component {
  componentDidMount() {
    this.state = { typeDevice: "codrone" };
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(el) {

  }

  render() {
    const zumiUrl = global.ZUMI_URL +'/notebooks/Untitled1.ipynb';
      return (
        <div className="master-workspace">
          <div className="loader"></div>
          <iframe id="iframeJupyter" src=''></iframe>
        </div>
        );
  }
}

export default MasterWorkspace;
