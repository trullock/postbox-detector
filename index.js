import RBush from "rbush/index.js";
import postboxes from "./postboxes.json" assert { type: "json" }
import fs from "fs"
import knn from "rbush-knn/index.js";


const tree = new RBush();


let items = postboxes.map(i => ({ minX: i[4], maxX: i[4], minY: i[5], maxY: i[5]}));
tree.load(items);

let nearest = knn(tree, 52.9234,-1.2405, 5)
console.log(nearest);

//let treeJson = tree.toJSON();
//fs.writeFileSync("./tree.json", JSON.stringify(treeJson));