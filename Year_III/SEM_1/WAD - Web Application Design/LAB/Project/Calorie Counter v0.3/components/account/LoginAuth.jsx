import AuthField from "./AuthField";

function LoginAuth() {
    return (
      <form className="mt-6 flex flex-col gap-4">
        <AuthField htmlFor="username" type="text">
          Username / Email
        </AuthField>

        <div className="relative">
          <div className="w-full absolute">
            <a href="#" className="text-xs float-right text-gray-600 hover:underline" >
              Forget Password?
            </a>
          </div>

          <AuthField htmlFor="password" type="password">
            Password
          </AuthField>
        </div>

        <button className="mt-2 w-full px-4 py-2 tracking-wide text-white transition-colors duration-200 transform bg-gray-700 rounded-md hover:bg-gray-600 focus:outline-none focus:bg-gray-600">
          Login
        </button>
      </form>
    );
}

export default LoginAuth;