import Layout from "components/layouts/navigation/Layout";
import ProfilePage from "components/profile/ProfilePage";
import { GetServerSideProps } from "next";

interface Props {
    uid: string;
}

export default function Index({ uid }: Props) {
    return (
        <Layout>
            <ProfilePage uid={uid} />
        </Layout>
    )
}

export const getServerSideProps: GetServerSideProps = async (context) => {
    const userId = context.query.userId;
    
    return {
        props: {
            uid: userId,
        }
    }
}