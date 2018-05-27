

var treeItems = [];
var treeItemCount;

function visualizeTree()
{
	if(data != null)
	{
		treeDrawerBegin();
	}
}


function visualizeDataBox()
{

}



function treeDrawerBegin()
{

	treeItemCount = 0;


	var i = rootIndex;

	var depth = 0;

	var w = width/ (Math.pow(2,depth)+1);
    w = w* data[i][3];
    var h = 50*depth +30;



	if(data[i][1] >= 0)
	{
		treeLineDrawer(data[i][1] , depth+1 , w ,h);
		treeNodeDrawer( data[i][1] , depth+1);

	}
	if(data[i][2] >= 0)
	{
		treeLineDrawer(data[i][2] , depth+1,  w ,h);
		treeNodeDrawer( data[i][2] , depth+1);
	}

	  drawNode(w , h ,i)
}



function treeLineDrawer(i , depth , x ,y)
{
	var w = width/ (Math.pow(2,depth)+1);
    w = w* data[i][3];
    var h = 50*depth +30;

	ctx.beginPath();
    ctx.moveTo(x,y);
    ctx.lineTo(w,h);
    ctx.stroke();




	if(data[i][1] >= 0)
	{

		treeLineDrawer(data[i][1] , depth+1 ,  w ,h);


	}
	if(data[i][2] >= 0)
	{
		treeLineDrawer(data[i][2] , depth+1, w ,h);
	}

}

function treeNodeDrawer(i , depth )
{
	var w = width/ (Math.pow(2,depth)+1);
    w = w* data[i][3];
    var h = 50*depth +30;

    drawNode(w , h ,i);



	if(data[i][1] >= 0)
	{

		treeNodeDrawer(data[i][1] , depth+1);


	}
	if(data[i][2] >= 0)
	{
		treeNodeDrawer(data[i][2] , depth+1);
	}
}