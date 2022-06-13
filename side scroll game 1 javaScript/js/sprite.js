const gravity = 0.7;
class Sprite{
    constructor({position, velocity, color = 'red', offset}){
        this.position = position;
        this.velocity = velocity;
        this.width = 50;
        this.height = 150;
        this.lastKeyPressed;
        this.attacking = false;
        this.attackBox = {
            position:{
                x: this.position.x,
                y: this.position.y
            },
            offset,
            width: 100,
            height: 50
        }
        this.color = color;
        this.health = 100;
    }

    draw(canvasContext){
        canvasContext.fillStyle = this.color;
        canvasContext.fillRect(this.position.x, this.position.y, this.width, this.height);
        //Attack Box//
        if(this.isAttacking()){

            canvasContext.fillStyle = 'green';
            canvasContext.fillRect(
                this.attackBox.position.x, 
                this.attackBox.position.y, 
                this.attackBox.width, 
                this.attackBox.height
            );
        }
    }

    update(canvasContext, height){
        this.draw(canvasContext);
        this.attackBox.position.y = this.position.y;
        this.attackBox.position.x = this.position.x + this.attackBox.offset.x;

        this.position.y += this.velocity.y;
        this.position.x += this.velocity.x;
        if(this.position.y + this.height + this.velocity.y >= height){
            this.velocity.y = 0;
        }else{
            this.velocity.y += gravity;
        }
    }

    canAttack(enemy){
        let a = this.attackBox.position.x + this.attackBox.width >= enemy.position.x;
        let b = this.attackBox.position.x <= enemy.position.x + enemy.width;
        let c = this.attackBox.position.y + this.attackBox.height >= enemy.position.y;
        let d = this.attackBox.position.y <= enemy.position.y + enemy.height;
        return a&&b&&c&&d;
    }

    isAttacking(){
        return this.attacking;
    }

    attack(){
        this.attacking = true;
        setTimeout(()=>{
            this.stopAttack();
        }, 100);
    }
    stopAttack(){
        this.attacking = false;
    }

    isDead(){
        return (this.health <= 0);
    }

    currentHealth(){
        return this.health;
    }

    jump(){
        this.velocity.y = -20;
    }

    stop(){
        this.velocity.x = 0;
    }
}

export default Sprite;