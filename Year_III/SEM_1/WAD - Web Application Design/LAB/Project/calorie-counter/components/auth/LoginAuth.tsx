import Button from 'components/common/Button';
import TextField from 'components/common/TextField';
import Router from 'next/router';

export default function LoginAuth() {
    const handleLogin = () => {
        // TODO: Login
        Router.push('./home')
    }

    return (
        <form className="mt-6 flex flex-col gap-4">
            <TextField label="Username / Email" type="text" />

            <div className="relative">
                <div className="w-full absolute">
                    <a href="#" className="text-xs float-right text-gray-600 hover:underline" >
                        Forget Password?
                    </a>
                </div>

                <TextField label="Password" type="password" />
            </div>

            <Button onClick={handleLogin}>
                Login
            </Button>
        </form>
    );
}