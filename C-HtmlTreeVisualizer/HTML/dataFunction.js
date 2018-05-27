dataFunction = function(i)
{
	 var res = data[i][0].split(',');

	 var output ="<b>"+res[0] + "</b>";


	 for (var i = 1; i < res.length; i++)
	  {

		 output+= "<br> "+ res[i]  + " : ";
		 var element = findFriendName(res[i]);
		 if(element)
		 {
		 	output += "<i>"+element +"</i>";
		 }else
		 {
		 	output += "?";
		 }
	  }


	 return output;
}


function DrawTooltip( x,y ,id)
{

	infoBox.style.display = "block";

   var rect = canvas.getBoundingClientRect();
   infoBox.style.left = rect.left+x +"px";
    infoBox.style.top = rect.top+y +"px";

    infoBox.innerHTML = dataFunction(id);




}
function CloseTooltip()
{
	infoBox.style.display="none"
}



function findFriendName(id)
{
	var i = 0;
	while( i < data.length && data[i][4] != id) 
	{
		i++;
	}

	if(i < data.length)
	return (data[i][0].split(' '))[0];
else 
	return null;
}