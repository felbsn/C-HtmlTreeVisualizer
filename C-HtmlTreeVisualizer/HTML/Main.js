        
window.onload = draw;

function refleshData()
{
 location.reload(); 
}    

function stopAutoReflesh()
{
    document.getElementById("btn_reflesh").style ="width:300px;" ;
    document.getElementById("btn_stopReflesh").style ="width:300px; background: lightblue; " 
    autoReflesh = false;
}

      
 var infoBox;
 var infoText;
 var autoReflesh =true;
 var focus = false;
 var canvas;
 var ctx;
 var width;
 var height;

    function draw()
        {

       infoBox = document.getElementById("infoBox");
       infoText = document.getElementById("infoText");
       canvas = document.getElementById('canvas');     
       ctx = canvas.getContext('2d');


            width = canvas.width;
            height = canvas.height;

            ctx.fillStyle ="white";
            ctx.fillRect(0 , 0 , width ,height);



         setTimeout(function() {
         if(!focus)
         if(autoReflesh)
         location.reload();
          }, 800);


        canvas.addEventListener('mousemove', OnNodeClick, false);


            visualizeTree();

         }
        

    function getCookie(name) {

  match = document.cookie.match(new RegExp(name + '=([^;]+)'));
  if (match) return match[1];
     /*var value = "; " + document.cookie;
     var parts = value.split("; " + name + "=");
     if (parts.length == 2) return parts.pop().split(";").shift();*/
    }

    function setCookie(name,value,days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days*24*60*60*1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + (value || "")  + expires + "; path=/";
}
        
    function drawTree()
    {
        var width = canvas.width;
        var height = canvas.height;
        
        var cWidth = width/2;
        var cHeight = nodeRadius*2;// padding etc..
        
        var treeLen = data.length+1;
        treeLen *= 8;
        metaWidth =  treeLen;
        
        metaHeight = 60;
        metaWidth = metaHeight / Math.sqrt(3);
        
    }
        


    function OnNodeClick(event) {
         var rect = canvas.getBoundingClientRect();
         var x = event.clientX - rect.left;
         var y = event.clientY - rect.top;

        for (var i = 0; i < treeItems.length; i++) {

           var xlen = treeItems[i].xPos - x;
           var ylen = treeItems[i].yPos - y;


          focus = true;
           if(Math.pow(xlen, 2)+Math.pow(ylen, 2) < Math.pow(nodeRadius,2) )
           {
            DrawTooltip(x , y , treeItems[i].src);
            return;
           }

        }

        if(autoReflesh)
        refleshData();

        focus = false;
        CloseTooltip();
    }



        function drawNode(x , y ,i )
    {

        treeItems.push({value:data[i][4] ,src:i ,xPos:x ,yPos:y });

        ctx.fillStyle = "white";
           // ctx.fillRect(x , y ,nodeWidth , nodeHeight);
            
            ctx.beginPath();
            ctx.arc(x,y,nodeRadius,0,2*Math.PI);
                  
            ctx.fill();
            ctx.stroke();
            
            ctx.fillStyle = "black";
            ctx.font="14px Georgia";
            ctx.textAlign="center"; 

            ctx.fillText(data[i][4].toString(), x, y+4);
           // wrapText(ctx ,data[i][4].toString(), x  ,y , nodeRadius ,nodeRadius);
    }



        function wrapText(context, text, x, y, maxWidth, lineHeight) {
        var words = text.split(' ');
        var line = '';

        for(var n = 0; n < words.length; n++) {
          var testLine = line + words[n] + ' ';
          var metrics = context.measureText(testLine);
          var testWidth = metrics.width;
          if (testWidth > maxWidth && n > 0) {
            context.fillText(line, x, y);
            line = words[n] + ' ';
            y += lineHeight;
          }
          else {
            line = testLine;
          }
        }
        context.fillText(line, x, y);
      }
