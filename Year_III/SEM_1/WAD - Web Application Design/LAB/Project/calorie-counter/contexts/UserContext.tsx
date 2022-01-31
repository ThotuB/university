import { createContext, useContext, useEffect, useState } from "react"
import { auth } from 'utils/firebase'
import {
    createUserWithEmailAndPassword,
    signInWithEmailAndPassword,
    UserCredential,
    User,
    signOut,
    signInWithPopup,
    GoogleAuthProvider,
    TwitterAuthProvider,
    updateProfile
} from 'firebase/auth'
import { isAdmin, makeUserAdminWithToken } from "services/user"

interface UserContext {
    user: User | null;
    admin: boolean;
    logIn: (email: string, password: string) => Promise<UserCredential>;
    logInGoogle: () => Promise<UserCredential>;
    logInTwitter: () => Promise<UserCredential>;
    logOut: () => Promise<void>;
    signUp: (email: string, password: string) => Promise<UserCredential>;
    update: (user: User, displayName: string) => Promise<void>;
    makeUserAdmin: (user: User, token: string) => Promise<void>;
}

const UserContext = createContext({} as UserContext)

export function useUser() {
    return useContext(UserContext)
}

interface UserProviderProps {
    children: React.ReactNode;
}

export function UserProvider({ children }: UserProviderProps) {
    const [user, setUser] = useState<User | null>({} as User)
    const [admin, setAdmin] = useState(false)

    const signUp = (email: string, password: string) => {
        return createUserWithEmailAndPassword(auth, email, password)
    }

    const logIn = (email: string, password: string) => {
        return signInWithEmailAndPassword(auth, email, password)
    }

    const logInGoogle = () => {
        return signInWithPopup(auth, new GoogleAuthProvider())
    }

    const logInTwitter = () => {
        return signInWithPopup(auth, new TwitterAuthProvider())
    }

    const logOut = () => {
        return signOut(auth)
    }

    const update = (user: User, username: string) => {
        return updateProfile(user, {
            displayName: username
        })
    }

    const makeUserAdmin = (user: User, token: string) => {
        return makeUserAdminWithToken(user.uid, token)
    }

    useEffect(() => {
        const unsubscribe = auth.onAuthStateChanged(user => {
            setUser(user)
            if (user) {
                isAdmin(user.uid)
                    .then(a => {
                        setAdmin(a)
                    })
            }
        })

        return unsubscribe
    }, [])

    const value = {
        user,
        admin,
        logIn,
        logInGoogle,
        logInTwitter,
        logOut,
        signUp,
        update,
        makeUserAdmin
    }

    return (
        <UserContext.Provider value={value}>
            {children}
        </UserContext.Provider>
    )
}