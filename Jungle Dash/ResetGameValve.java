public class ResetGameValve implements Valve {
    Player p;

    public ResetGameValve(Player p){
        this.p = p;
    }

    @Override
    public ValvesResponse execute(Message message) {
        if(message.getClass() != ResetGameMessage.class){
            return ValvesResponse.MISS;
        }
        p.revive();
        return ValvesResponse.EXECUTED;
    }
}
