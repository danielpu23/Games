public class DoDuckValve implements Valve {
    Player p;

    public DoDuckValve(Player p){
        this.p = p;
    }

    @Override
    public ValvesResponse execute(Message message) {
        if(message.getClass() != DuckMessage.class){
            return ValvesResponse.MISS;
        }
        p.duck();
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
