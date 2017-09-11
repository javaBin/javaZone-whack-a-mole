// Number of "iterations" the game lasts. Here each "iteration" is set to 1000 ms (see next line)
var count=3;

//1000 will run it every 1 second
var counter=setInterval(timer, 1000);

function timer()
{
  count=count-1;
  if (count <= 0)
  {
     clearInterval(counter);
     document.getElementById("timer").innerHTML="Done";
     window.location.href = "/showscore";
     return;
  }
 document.getElementById("timer").innerHTML=count + " secs";
}