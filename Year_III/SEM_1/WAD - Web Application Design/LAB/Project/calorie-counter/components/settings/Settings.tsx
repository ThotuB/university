import Layout from 'components/layouts/navigation/Layout';
import AdminApplication from './pages/AdminApplication';
import ChangePassword from './pages/ChangePassword';
import EditProfile from './pages/EditProfile';
import Preferences from './pages/Preferences';
import { SettingGroup, SettingPage } from './Setting';

export default function Settings() {
    return (
        <Layout>
            <SettingGroup>
                <SettingPage title="Edit Profile">
                    <EditProfile />
                </SettingPage>
                <SettingPage title="Change Password">
                    <ChangePassword />
                </SettingPage>
                <SettingPage title="Preferences">
                    <Preferences />
                </SettingPage>
                <SettingPage title="Admin Application">
                    <AdminApplication />
                </SettingPage>
            </SettingGroup>
        </Layout>
    )
}