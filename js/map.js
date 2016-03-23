function Map(w, h) {
    var map = [];

    for (var x = 0; x < w; x++) {
        for (var y = 0; y < h; y++) {
            map[y + x * h] = {
                free: true,
                x: x,
                y: y
            };
        }
    }

    this.map = map;

    /*this.setTileValue = function(x, y, value) {
        map[y + x * h].value = value;
    };*/

    this.getTile = function(x, y) {
        return map[y + x * h];
    }
}

module.exports = Map;
