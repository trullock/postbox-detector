#include <queue>
#include <vector>
#include "./node.h"

struct
{
	double dist;
} Item;


struct
{
	bool operator()(const Item a, const Item b) const { return a.dist > b.dist; }
} compareDist;

Results knn(tree, const double& x, const double& y, const int& n) {
    Node node = tree.data,
    std::vector result;
	toBBox = tree.toBBox,
	unsigned int i;
	Node child;
	double dist
	candidate;

	std::priority_queue<int> queue(data.begin(), data.end(), compareDist);

    while (node) {
        for (i = 0; i < node.count; i++) {
            child = node.children[i];
            dist = boxDist(x, y, node.leaf ? toBBox(child) : child);
			queue.push({
				node: child,
				isItem: node.leaf,
				dist: dist
			});
        }

        while (queue.length && queue.peek().isItem) {
            candidate = queue.pop();
            result.push(candidate);
            if (n && result.length === n) return result;
        }

        node = queue.pop();
        if (node) node = node.node;
    }

    return result;
}


double boxDist(const double& x, const double& y, box) {
    double dx = axisDist(x, box.minX, box.maxX);
    double dy = axisDist(y, box.minY, box.maxY);
    return dx * dx + dy * dy;
}

double axisDist(const double& k, const double& min, const double &max) {
    return k < min ? min - k : k <= max ? 0 : k - max;
}
