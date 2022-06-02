class Sprite{
    constructor(position){
        this.position = position;
    }

    draw(canvasContext){
        canvasContext.fillStyle = 'red';
        canvasContext.fillRect(this.position.x, this.position.y, 50, 150);
    }
}

export default Sprite;