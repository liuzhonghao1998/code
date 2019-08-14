function getCookie(name) {
    var cookieValue = null;
    if (document.cookie && document.cookie != '') {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = jQuery.trim(cookies[i]);
            // Does this cookie string begin with the name we want?
            if (cookie.substring(0, name.length + 1) == (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}
function csrfSafeMethod(method) {
    // these HTTP methods do not require CSRF protection
    return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

function like_change(obj,id){
        var data = {
            "id":id,
        }
        var elem = $(obj.getElementsByClassName('thumb_up'));
        var element = $(obj.getElementsByClassName('glyphicon'));$.ajax({
            url:/thumb_up/,
            type:'GET',
            data:data,
            success : function(data){
                console.log(data)
                if(data['status'] ==1){

                    element.addClass('active');
                    //update number
                    elem.text(data['num']);
                }
                else{
                    element.removeClass('active');
                    elem.text(data['num']);
                }

            },
            error:function(xhr){
                 console.log(xhr)
            }
        });
    }