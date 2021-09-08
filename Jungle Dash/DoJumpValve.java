public class DoJumpValve implements Valve {
    Player p;

    public DoJumpValve(Player p){
        this.p = p;
    }

    @Override
    public ValvesResponse execute(Message message) {
        if(message.getClass() != JumpMessage.class){
            return ValvesResponse.MISS;
        }
        p.jump();
        new java.util.Timer().schedule(            // set a delay for how long the Player is in the air before returning back to the ground
                new java.util.TimerTask() {
                    @Override
                    public void run() {
                        p.defaultPosition();
                    }
                },
                400
        );
        return ValvesResponse.EXECUTED;
    }
}
