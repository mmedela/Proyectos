const gravity = 0.2;
class Sprite{
    constructor({position, velocity}){
        this.position = position;
        this.velocity = velocity;
        this.height = 150;
    }

    draw(canvasContext){
        canvasContext.fillStyle = 'red';
        canvasContext.fillRect(this.position.x, this.position.y, 50, this.height);
    }

    update(canvasContext, height){
        this.draw(canvasContext);
        this.position.y += this.velocity.y;
        if(this.position.y + this.height + this.velocity.y >= height){
            this.velocity.y = 0;
        }else{
            this.velocity.y += gravity;
        }
    }
}

export default Sprite;