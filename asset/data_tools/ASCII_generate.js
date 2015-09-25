var fs = require('fs');

var convert = function(path1,path2){
	var res = [];
	var dat = fs.readFileSync(path1,'utf-8');
	var array = dat.split('\n');
	for(var i in array){
		if(array[i] === '')
			continue;
		var row = array[i].split(',');
		res.push(row.slice(0,-1).join(','));
	}

	console.log(res.join('\n'));
	fs.writeFileSync(path2,res.join('\n'),'ASCII');
}

convert('../plane_data.csv','../plane_ascii.csv');
convert('../carrier_data.csv','../carrier_ascii.csv');