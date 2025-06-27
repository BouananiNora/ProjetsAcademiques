package hepl.GestionHoraire.model.authentication;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

public class MapAuthenticatorTest
{
    private MapAuthenticator auth;

    @BeforeEach
    public void setup() {
        auth = new MapAuthenticator();
        auth.addUser("bob", "bob123");
    }

    @Test
    public void testAuthenticateSuccess() {
        boolean result = auth.authenticate("bob", "bob123");
        assertEquals(true, result);
    }

    @Test
    public void testAddUserSuccess() {
        boolean added = auth.addUser("alice", "alicepass");
        boolean canAuth = auth.authenticate("alice", "alicepass");

        assertEquals(true, added);
        assertEquals(true, canAuth);
    }

    @Test
    public void testAddUserDuplicate() {
        boolean added = auth.addUser("bob", "anotherpass");
        assertEquals(false, added);
    }

    @Test
    public void testCheckPasswordCorrect() {
        boolean result = auth.checkPassword("bob", "bob123");
        assertEquals(true, result);
    }

}
