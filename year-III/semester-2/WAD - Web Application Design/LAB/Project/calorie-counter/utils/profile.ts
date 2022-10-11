import { User } from "firebase/auth";
import { updateUserProfile } from "services/user";

export const createProfile = async ({ uid, displayName, email, phoneNumber, photoURL }: User) => {
    return await updateUserProfile({
        uid: uid,
        name: displayName || "",
        email: email || "",
        phone: phoneNumber || "",
        image: photoURL || "",
        website: "",
        bio: "",
        gender: "",
        isAdmin: false
    })
}