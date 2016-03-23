function LoadState() {

}

LoadState.prototype.preload = function() {
    this.load.image('wall', 'assets/wall.png');
}

LoadState.prototype.create = function() {
    this.state.start('gameState');
}


module.exports = LoadState;
