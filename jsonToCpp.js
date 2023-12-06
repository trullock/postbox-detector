import postboxes from "./postboxes.json" assert { type: "json" }
import fs from "fs"


let clean = postboxes.map(i => [i[4], i[5]]);

let count = clean.length;

let cpp = `#ifndef Postboxes_h
#define Postboxes_h

#define postboxCount ${count}

double postboxes[${count}][2] = {
	${clean.map(p => `{ ${p[0]}, ${p[1]} }`).join(",\n	")}
};

#endif`;

fs.writeFileSync("./postboxes.h", cpp)