import axios, { AxiosResponse } from "axios";
import { ProfileDto } from "types/profile";

export const makeUserAdminWithToken = async (userId: string, token: string) => {
    const url = `http://localhost:3000/api/user/admin`;
    const query = {
        params: {
            token: token,
        }
    }

    await axios.post(url, { uid: userId }, query);
}

export const isAdmin = async (userId: string) => {
    const url = `http://localhost:3000/api/user/admin/${userId}`;

    const { data } = await axios.get(url);

    return data ? true : false;
}

export const getUserProfile = async (userId: string): Promise<AxiosResponse<ProfileDto>> => {
    const url = `http://localhost:3000/api/user/profile/${userId}`;

    return await axios.get(url);
}

export const updateUserProfile = async (user: ProfileDto) => {
    const url = `http://localhost:3000/api/user/profile/${user.uid}`;

    return await axios.put(url, user);
}
