$(document).ready(function() {
  $('#take-photo').click(function() {
   $.ajax("http://zumi:2348", {
    data: {
      text: 'take-photo'
    },
    method: 'POST',
    xhrFields: {
      withCredentials: true
    },
    crossDomain: true,
    async: false,
    success: function(data) {
    },
    error: function(data) {}
  });
      
  alert('loading...');
      
  setTimeout(function() {
      window.location.reload();
  }, 5000);

  });
});
