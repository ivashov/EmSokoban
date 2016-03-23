Map = require("map.js");

function GameState() {

}

GameState.prototype.create = function() {
    var map = this.createMap();

    for (var i = 0; i < map.map.length; i++) {
        var tile = map.map[i];

        if (!tile.free) {
            tile.sprite = this.add.sprite(tile.x * 32, tile.y * 32, 'wall');
        }
    }

    this.map = map;
}

GameState.prototype.createMap = function() {
    map = new Map(10, 10);

    for (var i = 0; i < map.map.length; i++) {
        var tile = map.map[i];

        tile.free = Math.random() < 0.6;
    }

    return map;
}

module.exports = GameState;
