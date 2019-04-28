var partida = JSON.parse(data);
var aux = JSON.parse(partidaValues);

var tabla   = document.createElement('table');
	var tblBody = document.createElement('tbody');

	var hilera1 = document.createElement("tr");


	 var nome1 = document.createElement("th");
	 nome1.appendChild(document.createTextNode("NAME"));
	 hilera1.appendChild(nome1);
	 var altura1 = document.createElement("th");
	 altura1.appendChild(document.createTextNode("HEIGHT"));
	 hilera1.appendChild(altura1);

	 for(var i = 1; i <= aux.nr;i++){
	 	var celda1 = document.createElement("th");
	    celda1.appendChild(document.createTextNode("RONDA N"+i));
	    hilera1.appendChild(celda1);

	    var intentos1 = document.createElement("th");
	    intentos1.appendChild(document.createTextNode("TRY"));
	    hilera1.appendChild(intentos1);
	 }

	 var pontos1 = document.createElement("th");
	    pontos1.appendChild(document.createTextNode("PTS"));
	    hilera1.appendChild(pontos1);
	var per1 = document.createElement("th");
	    per1.appendChild(document.createTextNode("PTS%"));
	    hilera1.appendChild(per1);

	 tblBody.appendChild(hilera1);

	
	for (var i = 0; i < aux.nj; i++) {
 		var pts =0;
 		var t = 0;
 		var e = 0;
	  var hilera = document.createElement("tr");


	  var nome = document.createElement("td");
	  nome.appendChild(document.createTextNode(partida[i].name));
	  hilera.appendChild(nome);
	  var altura = document.createElement("td");
	  altura.appendChild(document.createTextNode(partida[i].height));
	  hilera.appendChild(altura);
	  for (var j = 0; j < aux.nr; j++) {

	    var celda = document.createElement("td");
	    celda.appendChild(document.createTextNode(partida[i].rondas[j].pontos));
	    hilera.appendChild(celda);
	    pts+=partida[i].rondas[j].pontos;
	    var intentos = document.createElement("td");
	    if(partida[i].rondas[j].pontos>0){
	    	intentos.appendChild(document.createTextNode(partida[i].rondas[j].tentativas+1));
	    	t+=partida[i].rondas[j].tentativas+1;
	    }
	    	
	    else{
	    	intentos.appendChild(document.createTextNode(partida[i].rondas[j].tentativas));
	    	t+=partida[i].rondas[j].tentativas;
	    }
	    e += partida[i].rondas[j].tentativas;
	    hilera.appendChild(intentos);
	  }
	 
	  var pontos = document.createElement("td");
	    pontos.appendChild(document.createTextNode(pts));
	    hilera.appendChild(pontos);
	var per = document.createElement("td");
	var porcentaje = Number(((t-e)/t*100).toFixed(1));
	    per.appendChild(document.createTextNode(porcentaje));
	    hilera.appendChild(per);

	  tblBody.appendChild(hilera);
	}
	 
	tabla.appendChild(tblBody);
	var body = document.getElementById("div1")
	body.appendChild(tabla);
	tabla.setAttribute("border-spacing", "0");
	tabla.setAttribute("border-collapse", "collapse");
