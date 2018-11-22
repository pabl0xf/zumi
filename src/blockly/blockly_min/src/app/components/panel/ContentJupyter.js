import React, { Component } from "react";
import ReactDOM from "react-dom";

class ContentJupyter extends React.Component {
  componentDidMount() {
    // Update src to iframe
    // https://localhost:8000/  | basecamp.robolink.com/cwists/category

  }


  render() {
    const zumiUrl = global.ZUMI_URL +'/notebooks/Untitled1.ipynb';
    return (
      <div className="content-panel content-5">
        <div className="loadeer"></div>
      
      </div>
    );
  }
}

export default ContentJupyter;
