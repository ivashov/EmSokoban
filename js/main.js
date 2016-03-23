Map = require("map.js");

console.log("Init");

var game = new Phaser.Game(800, 600, Phaser.AUTO, '');
game.state.add("loadState", require('./states/loadState.js'));
game.state.add("gameState", require('./states/gameState.js'));

game.state.start("loadState");
